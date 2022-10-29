#include "Systems/InputsManager.h"


void InputsManager::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	/*for (auto const& pair : inputFunctionMap)
	{
		if (key == pair.first && action == GLFW_PRESS)
		{
			pair.second();
		}
	}*/
}

void InputsManager::setInputCallBacks(std::map<int, Function> inputFunctionMap)
{
	inputFunctionMap_ = inputFunctionMap;

	glfwSetKeyCallback(window_, InputsManager::key_callback);
}

void InputsManager::setInputCallBacks()
{
	glfwSetKeyCallback(window_, key_callback);
}