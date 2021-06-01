#include "Input.h"

static GLFWwindow* window = nullptr;

void Input::setWindow(GLFWwindow* newWindow) {
	window = newWindow;
}

int Input::isKeyPressed(int keyCode) {
	if (window == nullptr) return false;
	return glfwGetKey(window, keyCode) == GLFW_PRESS;
}
