#include "Systems/Render.h"
#include "CoreECS/Coordinator.h"
#include <iostream>

void error_callback(int error, const char* description)
{
	std::cerr << "Error: %s" << std::endl;
	std::cerr << description << std::endl;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

Render::Render()
{
	glfwSetErrorCallback(error_callback);

	/* Initialize the library */
	if (!glfwInit())
		throw "Error in initialisation of glfw";

	/* Create a windowed mode window and its OpenGL context */
	window_ = glfwCreateWindow(640, 480, "Physical engine", NULL, NULL);
	if (!window_)
	{
		throw "Error in creating the window";
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window_);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		throw "Error in initialisation of glad";
	}

	glfwSetFramebufferSizeCallback(window_, framebuffer_size_callback);

	glEnable(GL_DEPTH_TEST);
}


Render::~Render()
{
	glfwDestroyWindow(window_);
	glDeleteVertexArrays(1, &VAO_);
	glDeleteBuffers(1, &vertexBuffer_);
	glDeleteProgram(program_);
	glfwTerminate();
}


void Render::update(float dt)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Coordinator* coordinator = Coordinator::getInstance();

	float ratio;
	int width, height;
	Camera& camera = coordinator->getComponent<Camera>(camera_);
	Vecteur3D lightPosition = coordinator->getComponent<Transform>(light_).getPosition();
	Vecteur3D lightColor = coordinator->getComponent<Light>(light_).getColor();
	Matrix4D view = camera.getViewMatrix();
	Matrix4D projection = camera.projectionMatrix();
	Vecteur3D posCamera = coordinator->getComponent<Transform>(camera_).getPosition();

	glfwGetFramebufferSize(window_, &width, &height);
	ratio = width / (float)height;
	camera.setRatio(ratio);

	glClearColor(0.13, 0.13, 0.13, 1.);
	glClear(GL_COLOR_BUFFER_BIT);

	GLfloat viewMatrix[16];
	view.toFloatArray(viewMatrix);


	shader_->use();
	glBindVertexArray(VAO_);
	//On charge les variables uniforme
	shader_->setUniformMatrix4fv("viewMatrix", (const GLfloat*)viewMatrix);
	shader_->setUniform3f("posLumiere", lightPosition.get_x(), lightPosition.get_y(), lightPosition.get_z());
	shader_->setUniform3f("posCamera", posCamera.get_x(), posCamera.get_y(), posCamera.get_z());
	shader_->setUniform3f("coulLumiere", lightColor.get_x(), lightColor.get_y(), lightColor.get_z());
	shader_->setUniform3f("coulObjet", 1.0f, 0.5f, 0.31f);
	shader_->setUniform3f("specLumiere", 1, 1, 1);
	shader_->setUniform3f("specObjet", 1, 1, 1);
	shader_->setUniform1f("alpha", 6);


	//On boucle sur tous les gameObjects pour changer la modelMatrix et la mvpMatrix et la normalMatrix
	int currentIndex = 0;

	for (auto gameObject : entities_)
	{
		if (coordinator->hasComponent<Object3D>(gameObject))
		{
			auto object = coordinator->getComponent<Object3D>(gameObject);
			auto transform = coordinator->getComponent<Transform>(gameObject);
			int length = object.getIndices().size();

			Matrix4D model = transform.getModelMatrix();
			Matrix4D mvp = (projection * view * model);
			Matrix4D modelView = view * model;

			Matrix3D normalMatrix = camera.getNormalMatrix(model);

			GLfloat normalMat[9];
			normalMatrix.toFloatArray(normalMat);

			GLfloat MVP[16];
			mvp.toFloatArray(MVP);

			GLfloat modelMatrix[16];
			model.toFloatArray(modelMatrix);

			shader_->setUniformMatrix3fv("normalMatrix", (const GLfloat*)normalMat);
			shader_->setUniformMatrix4fv("MVP", (const GLfloat*)MVP);
			shader_->setUniformMatrix4fv("modelMatrix", (const GLfloat*)modelMatrix);

			glDrawElements(GL_TRIANGLES, length, GL_UNSIGNED_INT, &indices_[currentIndex]);
			currentIndex += length;
		}
	}

	/* Swap front and back buffers */
	glfwSwapBuffers(window_);
}

void Render::insertEntity(Entity entity)
{
	Coordinator *coordinator = Coordinator::getInstance();
	entities_.insert(entity);
	if (coordinator->hasComponent<Camera>(entity))
	{
		camera_ = entity;
	}
	else if (coordinator->hasComponent<Light>(entity))
	{
		light_ = entity;
	}

	if (coordinator->hasComponent<Object3D>(entity))
	{
		loadMeshes();
	}
}

void Render::setShader(Shader *shader)
{
	shader_ = shader;
	program_ = shader->getIDProgram();
}


void Render::loadMeshes()
{
	Coordinator* coordinator = Coordinator::getInstance();

	vertices_ = std::vector<Vertice>();
	indices_ = std::vector<unsigned int>();

	int currentIndex = 0;

	for (auto gameObject : entities_)
	{
		if (coordinator->hasComponent<Object3D>(gameObject))
		{
			auto meshes = coordinator->getComponent<Object3D>(gameObject);

			auto verticesObject = meshes.getVertices();
			auto indicesObject = meshes.getIndices();

			for (int i = 0; i < indicesObject.size(); i++)
			{
				indicesObject[i] += currentIndex;
			}
			vertices_.insert(vertices_.end(), verticesObject.begin(), verticesObject.end());
			indices_.insert(indices_.end(), indicesObject.begin(), indicesObject.end());
			currentIndex = vertices_.size();

		}
	}

	glGenBuffers(1, &vertexBuffer_);
	glGenBuffers(1, &EBO_);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer_);
	glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(Vertice), &vertices_[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(unsigned int), &indices_[0], GL_STATIC_DRAW);


	glGenVertexArrays(1, &VAO_);
	glBindVertexArray(VAO_);


	vposLocation_ = glGetAttribLocation(program_, "vPos");
	vcolLocation_ = glGetAttribLocation(program_, "vCol");
	normalLocation_ = glGetAttribLocation(program_, "normal");

	glEnableVertexAttribArray(vposLocation_);
	glVertexAttribPointer(vposLocation_, 3, GL_FLOAT, GL_FALSE, sizeof(vertices_[0]), (void*)0);
	glEnableVertexAttribArray(vcolLocation_);
	glVertexAttribPointer(vcolLocation_, 3, GL_FLOAT, GL_FALSE, sizeof(vertices_[0]), (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(normalLocation_);
	glVertexAttribPointer(normalLocation_, 3, GL_FLOAT, GL_FALSE, sizeof(vertices_[0]), (void*)(sizeof(float) * 6));
}
