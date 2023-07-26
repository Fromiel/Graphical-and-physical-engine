#include "Systems/MouseInputs.h"

int MouseInputs::oldState = GLFW_RELEASE;
GLFWwindow* MouseInputs::window = nullptr;

bool MouseInputs::IsLeftMouseDown()
{
	int newState = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
	if (oldState == GLFW_PRESS)
	{
		oldState = newState;
		return false;
	}
	oldState = newState;
	return newState == GLFW_PRESS;
}