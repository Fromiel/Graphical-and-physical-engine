#ifndef MOUSEINPUTS_H
#define MOUSEINPUTS_H

#include "IncludeGLFW.h"
#include <map>
#include <vector>

class MouseInputs
{
	private:
		static int oldState;
		static GLFWwindow* window;

	public:
		static void setWindow(GLFWwindow* w) { window = w; }

		/// <summary>
		/// Retourne true si le boutton est press� et false sinon
		/// </summary>
		/// <returns></returns>
		static bool IsLeftMouseDown();

};

#endif