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
	glfwTerminate();
}


void Render::update(float dt)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Coordinator* coordinator = Coordinator::getInstance();

	float ratio;
	int width, height;
	Camera& camera = coordinator->getComponent<Camera>(camera_);
	Light light = coordinator->getComponent<Light>(light_);
	Vecteur3D lightPosition = coordinator->getComponent<Transform>(light_).getPosition();
	Vecteur3D lightColor = light.getColor();
	Matrix4D view = camera.getViewMatrix();
	Matrix4D projection = camera.projectionMatrix();
	Vecteur3D posCamera = coordinator->getComponent<Transform>(camera_).getPosition();

	glfwGetFramebufferSize(window_, &width, &height);
	ratio = width / (float)height;
	camera.setRatio(ratio);

	glClearColor(0.13f, 0.13f, 0.13f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	GLfloat viewMatrix[16];
	view.toFloatArray(viewMatrix);



	for (auto gameObject : entities_)
	{

		if (coordinator->hasComponent<Object3D>(gameObject))
		{

			Material material;
			if (!coordinator->hasComponent<Material>(gameObject))
			{
				material = Material::getDefault();
			}
			else
			{
				material = coordinator->getComponent<Material>(gameObject);
			}
			Shader shader_ = material.getShader();
			shader_.use();

			//On charge les variables uniforme
			shader_.setUniformMatrix4fv("viewMatrix", (const GLfloat*)viewMatrix);
			shader_.setUniform3f("posLumiere", lightPosition.get_x(), lightPosition.get_y(), lightPosition.get_z());
			shader_.setUniform3f("posCamera", posCamera.get_x(), posCamera.get_y(), posCamera.get_z());
			shader_.setUniform3f("coulLumiere", lightColor.get_x(), lightColor.get_y(), lightColor.get_z());
			shader_.setUniform3f("coulObjet", material.getAmbient().get_x(), material.getAmbient().get_y(), material.getAmbient().get_z());
			shader_.setUniform3f("specLumiere", light.getSpecular().get_x(), light.getSpecular().get_y(), light.getSpecular().get_z());
			shader_.setUniform3f("specObjet", material.getSpecular().get_x(), material.getSpecular().get_y(), material.getSpecular().get_z());
			shader_.setUniform3f("diffuse", material.getDiffuse().get_x(), material.getDiffuse().get_y(), material.getDiffuse().get_z());
			shader_.setUniform1f("alpha", material.getAlpha());


			auto object = coordinator->getComponent<Object3D>(gameObject);
			auto transform = coordinator->getComponent<Transform>(gameObject);

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

			shader_.setUniformMatrix3fv("normalMatrix", (const GLfloat*)normalMat);
			shader_.setUniformMatrix4fv("MVP", (const GLfloat*)MVP);
			shader_.setUniformMatrix4fv("modelMatrix", (const GLfloat*)modelMatrix);

			auto type = coordinator->getComponent<Object3D>(gameObject).getType();

			auto test = lengths_[type];
			auto test2 = currentIndexes_[type];

			glBindVertexArray(VAO_);
			glDrawElements(GL_TRIANGLES, lengths_[type], GL_UNSIGNED_INT, &indices_[currentIndexes_[type]]);
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


void Render::loadMeshes()
{
	Coordinator* coordinator = Coordinator::getInstance();

	//vertices_ = std::vector<Vertice>();
	//indices_ = std::vector<unsigned int>();
	//currentIndexes_ = std::unordered_map<ObjectTypeEnum, GLuint>();
	//lengths_ = std::unordered_map<ObjectTypeEnum, GLuint>();


	for (auto gameObject : entities_)
	{
		if (coordinator->hasComponent<Object3D>(gameObject))
		{
			auto meshes = coordinator->getComponent<Object3D>(gameObject);
			auto type = meshes.getType();

			if (!currentIndexes_.count(type))
			{
				unsigned int currentIndex = static_cast<int>(vertices_.size());
				auto verticesObject = meshes.getVertices();
				auto indicesObject = meshes.getIndices();

				currentIndexes_[type] = static_cast<unsigned int>(indices_.size());

				for (int i = 0; i < indicesObject.size(); i++)
				{
					indicesObject[i] += currentIndex;
				}
				vertices_.insert(vertices_.end(), verticesObject.begin(), verticesObject.end());
				indices_.insert(indices_.end(), indicesObject.begin(), indicesObject.end());


				lengths_[type] = static_cast<unsigned int>(indicesObject.size());
			}
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

	int currentProgram_;

	for (auto gameObject : entities_)
	{
		if (coordinator->hasComponent<Object3D>(gameObject))
		{
			if (!coordinator->hasComponent<Material>(gameObject))
			{
				currentProgram_ = Material::getDefault().getShader().getIDProgram();
			}
			else
			{
				currentProgram_ = coordinator->getComponent<Material>(gameObject).getShader().getIDProgram();
			}

			vposLocation_ = glGetAttribLocation(currentProgram_, "vPos");
			normalLocation_ = glGetAttribLocation(currentProgram_, "normal");

			glEnableVertexAttribArray(vposLocation_);
			glVertexAttribPointer(vposLocation_, 3, GL_FLOAT, GL_FALSE, sizeof(vertices_[0]), (void*)0);
			glEnableVertexAttribArray(normalLocation_);
			glVertexAttribPointer(normalLocation_, 3, GL_FLOAT, GL_FALSE, sizeof(vertices_[0]), (void*)(sizeof(float) * 3));
		}
	}

}
