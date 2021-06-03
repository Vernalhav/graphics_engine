#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace Input {

	void setWindow(GLFWwindow* window);

	int isKeyPressed(int keyCode);

	void closeWindow();
	
};