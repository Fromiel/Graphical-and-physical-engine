#include "OpenGLManager.h"

void error_callback(int error, const char* description)
{
	std::cerr << "Error: %s" << std::endl;
	std::cerr << description << std::endl;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}



OpenGLManager::~OpenGLManager()
{
	glfwDestroyWindow(window_);
	glDeleteVertexArrays(1, &VAO_);
	glDeleteBuffers(1, &vertexBuffer_);
	glDeleteProgram(program_);
	glfwTerminate();
}

void OpenGLManager::initAndCreateWindow()
{
	glfwSetErrorCallback(error_callback);

	/* Initialize the library */
	if (!glfwInit())
		throw "Error in initialisation of glfw";

	/* Create a windowed mode window and its OpenGL context */
	window_ = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
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

}

void OpenGLManager::loadVertices(std::vector<Vertice> vertices, std::vector<unsigned int> indices, GLuint idProgram)
{
	vertices_ = vertices;
	indices_ = indices;
	program_ = idProgram;

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

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


void toGlFloat(Matrix3D matrix, GLfloat arr[])
{
	std::vector<double> content = matrix.getContentAsStdVector();
	std::copy(content.begin(), content.end(), arr);
}

void toGlFloat(Matrix4D matrix, GLfloat arr[])
{
	std::vector<double> content = matrix.getContentAsStdVector();
	std::copy(content.begin(), content.end(), arr);

}



void OpenGLManager::Render(Shader shader)
{

	float ratio;
	int width, height;
	Matrix4D model = object_.getModelMatrix();
	Matrix4D view = camera_.getViewMatrix();
	Matrix4D projection = Matrix4D::projectionMatrix(camera_.getFov(), camera_.getRatio(), camera_.getNear(), camera_.getFar());
	Matrix4D mvp = (projection * view * model).transpose(); //On applique la transposée car quand on va passer les matrices à glsl, il va construire les matrices colonne par colonne et non ligne par ligne comme nous
	Matrix4D modelView = view * model;
	Matrix3D upperLeftModelView;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			upperLeftModelView(i, j) = modelView(i, j);
		}
	}

	Matrix3D normalMatrix = upperLeftModelView.invert();
	Vecteur3D posCamera = camera_.getPosition();

	glfwGetFramebufferSize(window_, &width, &height);
	ratio = width / (float)height;

	glClearColor(0.13, 0.13, 0.13, 1.);
	glClear(GL_COLOR_BUFFER_BIT);

	GLfloat modelMatrix[16];
	toGlFloat(model.transpose(), modelMatrix);
	GLfloat viewMatrix[16];
	toGlFloat(view.transpose(), viewMatrix);
	GLfloat normalMat[9];
	toGlFloat(normalMatrix, normalMat);
	GLfloat MVP[16];
	toGlFloat(mvp, MVP);

	
	shader.use();
	glBindVertexArray(VAO_);
	//On charge les variables uniforme
	shader.setUniformMatrix4fv("MVP", (const GLfloat *) MVP);
	shader.setUniformMatrix4fv("modelMatrix", (const GLfloat*) modelMatrix);
	shader.setUniformMatrix4fv("viewMatrix", (const GLfloat*)viewMatrix);
	shader.setUniformMatrix3fv("normalMatrix", (const GLfloat*)normalMat);
	shader.setUniform3f("posLumiere", lightPosition_.get_x(), lightPosition_.get_y(), lightPosition_.get_z());
	shader.setUniform3f("posCamera", posCamera.get_x(), posCamera.get_y(), posCamera.get_z());
	shader.setUniform3f("coulLumiere", 1, 1, 1);
	shader.setUniform3f("coulObjet", 1.0f, 0.5f, 0.31f);
	shader.setUniform3f("specLumiere", 1, 1, 1);
	shader.setUniform3f("specObjet", 1, 1, 1);
	shader.setUniform1f("alpha", 6);

	glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_INT, &indices_[0]);
}