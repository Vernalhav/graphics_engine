#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace Input {

	/// <summary>
	/// Sets the specified window as the
	/// source of inputs
	/// </summary>
	void setWindow(GLFWwindow* window);

	/// <summary>
	/// Returns whether or not the keyCode
	/// (GLFW key enum) is pressed or not
	/// </summary>
	bool isKeyPressed(int keyCode);

	/// <summary>
	/// Sets the WindowShouldClose flag to true
	/// </summary>
	void closeWindow();
};