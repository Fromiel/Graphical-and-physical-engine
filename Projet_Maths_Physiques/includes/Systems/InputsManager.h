#ifndef INPUTSMANAGER_H
#define INPUTSMANAGER_H

#include "CoreECS/System.h"
#include "IncludeGLFW.h"
#include <map>
#include <iostream>

typedef void (*Function)();

/// <summary>
/// Syst�me g�rant les inputs de l'utilisateur (classe non finie)
/// </summary>
class InputsManager : public System
{
	private:
		bool endGame_;
		GLFWwindow* window_;//Fen�tre
		std::map<int, Function> inputFunctionMap_; //map liant les inputs � leur fonction

		/// <summary>
		/// M�thode appel�e lors de la gestion des inputs (static temporairement)
		/// </summary>
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

	public:
		/// <summary>
		/// Constructeur initialisant endGame � false
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
		/// Appelle les �v�nements
		/// </summary>
		void pollEvents() { glfwPollEvents(); }

		/// <summary>
		/// Set la fen�tre
		/// </summary>
		/// <param name="window"></param>
		void setWindow(GLFWwindow* window) { window_ = window; }

};

#endif 