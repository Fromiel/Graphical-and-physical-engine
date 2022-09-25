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
/// Class g�rant l'affichage avec opengl
/// </summary>
class OpenGLManager
{
	private:
		Scene scene_;
		std::vector<Vertice> vertices_; //les points � afficher
		std::vector<unsigned int> indices_; //les indices des points
		GLFWwindow* window_; //Fen�tre
		GLuint vertexBuffer_, vertexShader_, fragmentShader_, program_, VAO_, EBO_; //Differents id
		GLint vposLocation_, vcolLocation_, normalLocation_; //Id des attributes
		

	public:

		~OpenGLManager();

		/// <summary>
		/// M�thode initialisant glad et glfw et cr�ant une fen�tre
		/// </summary>
		void initAndCreateWindow();

		/// <summary>
		/// 
		/// </summary>
		/// <returns>La sc�ne</returns>
		Scene getScene() const { return scene_; }

		void setGameObject(int index, Object3D object) { scene_.setGameObject(index, object); }

		/// <summary>
		/// Appel la m�thode applyForces de la scene
		/// </summary>
		/// <param name="frameRate"></param>
		void updateScene(double frameRate) { scene_.applyForces(frameRate); }

		/// <summary>
		/// M�thode affectant la fonction � appel� pour g�rer les inputs
		/// </summary>
		/// <param name="key_callback">la fonction � appeler</param>
		void setKeyCallback(static void (*key_callback)(GLFWwindow*, int, int, int, int)) { glfwSetKeyCallback(window_, key_callback); };

		/// <summary>
		/// M�thode pour set l'id du programme
		/// </summary>
		/// <param name="ID">Nouvel ID</param>
		void setIdProgram(GLuint ID) { program_ = ID; }

		/// <summary>
		/// M�thode permettant de charger une sc�ne, ce qui va set vertices_ et indices_; ainsi que charger les attributes et de g�n�rer les buffers
		/// </summary>
		/// <param name="scene">La scene � charger</param>
		void loadScene(Scene scene);

		/// <summary>
		/// Retourne l'id de la fen�tre
		/// </summary>
		/// <returns></returns>
		GLFWwindow* getWindow() const { return window_; }

		/// <summary>
		/// Affiche  les points dans la fen�tre � l'aide du shader pass� en argument
		/// </summary>
		/// <param name="shader"></param>
		void Render(Shader shader);







		
};



#endif