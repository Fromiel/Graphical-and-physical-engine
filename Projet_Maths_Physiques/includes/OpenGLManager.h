#ifndef OPENGL_MANAGER_H
#define OPENGL_MANAGER_H

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include "Vertice.h"
#include "Vecteur3D.h"
#include "Matrix3D.h"
#include "Matrix4D.h"
#include "Shader.h"
#include "Object3d.h"
#include "Camera.h"
#include "Particule.h"

/// <summary>
/// Class gérant l'affichage avec opengl
/// </summary>
class OpenGLManager
{
	private:
		Object3D object_;
		Camera camera_;
		std::vector<Vertice> vertices_; //les points à afficher
		std::vector<unsigned int> indices_; //les indices des points
		Vecteur3D lightPosition_; //position de la lumière
		GLFWwindow* window_; //Fenêtre
		GLuint vertexBuffer_, vertexShader_, fragmentShader_, program_, VAO_, EBO_; //Differents id
		GLint vposLocation_, vcolLocation_, normalLocation_; //Id des attributes
		

	public:

		~OpenGLManager();

		/// <summary>
		/// Méthode initialisant glad et glfw et créant une fenêtre
		/// </summary>
		void initAndCreateWindow();

		/// <summary>
		/// Méthode affectant la fonction à appelé pour gérer les inputs
		/// </summary>
		/// <param name="key_callback">la fonction à appeler</param>
		void setKeyCallback(static void (*key_callback)(GLFWwindow*, int, int, int, int)) { glfwSetKeyCallback(window_, key_callback); };

		/// <summary>
		/// Set la position de la lumière
		/// </summary>
		/// <param name="lightPosition"></param>
		void setLightPosition(Vecteur3D lightPosition) { lightPosition_ = lightPosition; }

		/// <summary>
		/// Set l'objet3d
		/// </summary>
		/// <param name="object"></param>
		void setObject(Object3D object) { object_ = object; }

		/// <summary>
		/// Set la camera
		/// </summary>
		/// <param name="camera"></param>
		void setCamera(Camera camera) { camera_ = camera; }

		/// <summary>
		/// Méthode permettant de set vertices_, indices_ et program_; de charger les attributes et de générer les buffers
		/// </summary>
		/// <param name="vertices"></param>
		/// <param name="indices"></param>
		/// <param name="idProgram"></param>
		void loadVertices(std::vector<Vertice> vertices, std::vector<unsigned int> indices, GLuint idProgram);

		/// <summary>
		/// Retourne l'id de la fenêtre
		/// </summary>
		/// <returns></returns>
		GLFWwindow* getWindow() const { return window_; }

		/// <summary>
		/// Affiche  les points dans la fenêtre à l'aide du shader passé en argument
		/// </summary>
		/// <param name="shader"></param>
		void Render(Shader shader);





		
};



#endif