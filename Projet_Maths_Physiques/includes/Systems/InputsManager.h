#ifndef INPUTSMANAGER_H
#define INPUTSMANAGER_H

#include "CoreECS/System.h"
#include "KeyInput.h"
#include "MouseInputs.h"
#include <map>
#include <iostream>

/// <summary>
/// Syst�me g�rant les inputs de l'utilisateur
/// </summary>
class InputsManager : public System
{
	private:
		GLFWwindow* window_;
		static bool endGame_;

	public:

		/// <summary>
		/// G�re les actions voulues aux inputs
		/// </summary>
		void setupKeyInputs(GLFWwindow* window) { 
			KeyInput::setupKeyInputs(window);
			MouseInputs::setWindow(window);
			window_ = window;
		};

		/// <summary>
		/// Fonction pour savoir si il faut fermer le programme
		/// </summary>
		/// <returns>true si il faut fermer le programme, false sinon</returns>
		bool endGame() const { return glfwWindowShouldClose(window_) || endGame_; }
		
		/// <summary>
		/// Appelle les �v�nements
		/// </summary>
		void pollEvents() const { glfwPollEvents(); }

		/// <summary>
		/// Set endGame
		/// </summary>
		/// <param name="b"></param>
		static void setEndGame(bool b) { endGame_ = b; }

};

#endif 