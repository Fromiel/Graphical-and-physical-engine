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


OpenGLManager::OpenGLManager()
{

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


void OpenGLManager::Render(Shader shader)
{
	float ratio;
	int width, height;
	mat4x4 m, p, mvp;
	const GLfloat normalMatrix[9] = { 1, 0, 0 , 0, 1, 0, 0, 0, 1 };
	Vecteur3D posCamera(0.f, 0.f, 1.f);

	glfwGetFramebufferSize(window_, &width, &height);
	ratio = width / (float)height;

	glClearColor(0.9, 0.9, 0.9, 1.);
	glClear(GL_COLOR_BUFFER_BIT);



	mat4x4_identity(m);
	
	//mat4x4_rotate_Z(m, m, (float)glfwGetTime());
	mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
	mat4x4_mul(mvp, p, m);

	
	shader.use();
	glBindVertexArray(VAO_);
	shader.setUniformMatrix4fv("MVP", (const GLfloat*)mvp);
	shader.setUniformMatrix4fv("modelMatrix", (const GLfloat*)m);
	shader.setUniformMatrix3fv("normalMatrix", normalMatrix);
	shader.setUniform3f("posLumiere", lightPosition_.get_x(), lightPosition_.get_y(), lightPosition_.get_z());
	shader.setUniform3f("posCamera", posCamera.get_x(), posCamera.get_y(), posCamera.get_z());
	shader.setUniform3f("coulLumiere", 1, 1, 1);
	shader.setUniform3f("coulObjet", 0.3, 1, 0.6);
	shader.setUniform3f("specLumiere", 1, 1, 1);
	shader.setUniform3f("specObjet", 1, 1, 1);
	shader.setUniform1f("alpha", 0.5);

	//glDrawArrays(GL_TRIANGLE_STRIP, 0, vertices_.size());
	glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_INT, &indices_[0]);
}