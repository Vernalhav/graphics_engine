#include "Input.h"

static GLFWwindow* window = nullptr;

void Input::setWindow(GLFWwindow* newWindow) {
	window = newWindow;
}

bool Input::isKeyPressed(int keyCode) {
	if (window == nullptr) return false;
	return glfwGetKey(window, keyCode) == GLFW_PRESS;
}

void Input::closeWindow() {
	glfwSetWindowShouldClose(window, GLFW_TRUE);
}
