#ifndef INPUTSMANAGER_H
#define INPUTSMANAGER_H

#include "CoreECS/System.h"
#include "IncludeGLFW.h"
#include <map>
#include <iostream>

typedef void (*Function)();

/// <summary>
/// Système gérant les inputs de l'utilisateur (classe non finie)
/// </summary>
class InputsManager : public System
{
	private:
		bool endGame_;
		GLFWwindow* window_;//Fenêtre
		std::map<int, Function> inputFunctionMap_; //map liant les inputs à leur fonction

		/// <summary>
		/// Méthode appelée lors de la gestion des inputs (static temporairement)
		/// </summary>
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

	public:
		/// <summary>
		/// Constructeur initialisant endGame à false
		/// </summary>
		InputsManager() : endGame_(false) {}

		/// <summary>
		/// todo
		/// </summary>
		/// <param name="inputFunctionMap"></param>
		void setInputCallBacks(std::map<int, Function> inputFunctionMap);

		/// <summary>
		/// (temporaire) Dit a glfw d'appeler key_callback lors des inputs
		/// </summary>
		void setInputCallBacks();

		/// <summary>
		/// Fonction pour savoir si il faut fermer le programme
		/// </summary>
		/// <returns>true si il faut fermer le programme, false sinon</returns>
		bool endGame() { return glfwWindowShouldClose(window_) || endGame_; }

		/// <summary>
		/// Set endGame
		/// </summary>
		/// <param name="b"></param>
		void setEndGame(bool b) { endGame_ = b; }
		
		/// <summary>
		/// Appelle les évènements
		/// </summary>
		void pollEvents() { glfwPollEvents(); }

		/// <summary>
		/// Set la fenêtre
		/// </summary>
		/// <param name="window"></param>
		void setWindow(GLFWwindow* window) { window_ = window; }

};

#endif 