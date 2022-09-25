#ifndef OPENGL_MANAGER_H
#define OPENGL_MANAGER_H

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include "Vertice.h"
#include "Matrix3D.h"
#include "Matrix4D.h"
#include "Shader.h"
#include "Scene.h"
#include "Particule.h"

/// <summary>
/// Class gérant l'affichage avec opengl
/// </summary>
class OpenGLManager
{
	private:
		Scene scene_;
		std::vector<Vertice> vertices_; //les points à afficher
		std::vector<unsigned int> indices_; //les indices des points
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
		/// 
		/// </summary>
		/// <returns>La scène</returns>
		Scene getScene() const { return scene_; }

		void setGameObject(int index, Object3D object) { scene_.setGameObject(index, object); }

		/// <summary>
		/// Appel la méthode applyForces de la scene
		/// </summary>
		/// <param name="frameRate"></param>
		void updateScene(double frameRate) { scene_.applyForces(frameRate); }

		/// <summary>
		/// Méthode affectant la fonction à appelé pour gérer les inputs
		/// </summary>
		/// <param name="key_callback">la fonction à appeler</param>
		void setKeyCallback(static void (*key_callback)(GLFWwindow*, int, int, int, int)) { glfwSetKeyCallback(window_, key_callback); };

		/// <summary>
		/// Méthode pour set l'id du programme
		/// </summary>
		/// <param name="ID">Nouvel ID</param>
		void setIdProgram(GLuint ID) { program_ = ID; }

		/// <summary>
		/// Méthode permettant de charger une scène, ce qui va set vertices_ et indices_; ainsi que charger les attributes et de générer les buffers
		/// </summary>
		/// <param name="scene">La scene à charger</param>
		void loadScene(Scene scene);

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