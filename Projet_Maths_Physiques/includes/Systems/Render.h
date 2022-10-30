#ifndef RENDER_H
#define RENDER_H

#include <glad/glad.h>
#include "IncludeGLFW.h"

#include "CoreECS/System.h"
#include "CoreECS/Coordinator.h"
#include <vector>
#include "Vertice.h"
#include "Components.h"
#include "Shader.h"

/// <summary>
/// Syst�me g�rant l'affichage des gameobjects (entit�s)
/// </summary>
class Render : public System
{
	private:
		std::vector<Vertice> vertices_; //les points � afficher
		std::vector<unsigned int> indices_; //les indices des points
		std::unordered_map<Entity, GLuint> currentIndexes_;
		std::unordered_map<Entity, GLuint> lengths_;

		GLFWwindow* window_; //Fen�tre
		GLuint vertexBuffer_, vertexShader_, fragmentShader_, program_, VAO_, EBO_; //Differents id
		GLint vposLocation_, vcolLocation_, normalLocation_; //Id des attributes
		Entity camera_;
		Entity light_;
		Shader shader_;

	public:
		/// <summary>
		/// Constructeur initialisant la fen�tre et OpenGl
		/// </summary>
		Render();

		/// <summary>
		/// Destructeur lib�rant la m�moire prise par GLFW et OpenGl
		/// </summary>
		~Render();

		/// <summary>
		/// Met � jour la sc�ne
		/// </summary>
		/// <param name="dt"></param>
		void update(float dt);

		/// <summary>
		/// Retourne un pointeur vers la fen�tre du rendu graphique
		/// </summary>
		/// <returns></returns>
		GLFWwindow* getWindow() { return window_; }

		/// <summary>
		/// Override de la m�thode insertEntity pour d�tecter l'ajout d'une cam�ra et d'une lumi�re
		/// </summary>
		/// <param name="entity"></param>
		void insertEntity(Entity entity) override;

		/// <summary>
		/// Charge les ar�tes et les indices des objets dans le GPU
		/// </summary>
		void loadMeshes();



};


#endif