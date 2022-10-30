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
/// Système gérant l'affichage des gameobjects (entités)
/// </summary>
class Render : public System
{
	private:
		std::vector<Vertice> vertices_; //les points à afficher
		std::vector<unsigned int> indices_; //les indices des points
		std::unordered_map<Entity, GLuint> currentIndexes_;
		std::unordered_map<Entity, GLuint> lengths_;

		GLFWwindow* window_; //Fenêtre
		GLuint vertexBuffer_, vertexShader_, fragmentShader_, program_, VAO_, EBO_; //Differents id
		GLint vposLocation_, vcolLocation_, normalLocation_; //Id des attributes
		Entity camera_;
		Entity light_;
		Shader shader_;

	public:
		/// <summary>
		/// Constructeur initialisant la fenêtre et OpenGl
		/// </summary>
		Render();

		/// <summary>
		/// Destructeur libérant la mémoire prise par GLFW et OpenGl
		/// </summary>
		~Render();

		/// <summary>
		/// Met à jour la scène
		/// </summary>
		/// <param name="dt"></param>
		void update(float dt);

		/// <summary>
		/// Retourne un pointeur vers la fenêtre du rendu graphique
		/// </summary>
		/// <returns></returns>
		GLFWwindow* getWindow() { return window_; }

		/// <summary>
		/// Override de la méthode insertEntity pour détecter l'ajout d'une caméra et d'une lumière
		/// </summary>
		/// <param name="entity"></param>
		void insertEntity(Entity entity) override;

		/// <summary>
		/// Charge les arêtes et les indices des objets dans le GPU
		/// </summary>
		void loadMeshes();



};


#endif