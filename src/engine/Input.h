#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "Window.h"

class Input {
public:
	/// <summary>
	/// Sets the specified window as the
	/// source of inputs
	/// </summary>
	static void setWindow(Window* window);

	/// <summary>
	/// Returns whether or not the keyCode
	/// (GLFW key enum) is pressed or not
	/// </summary>
	static bool isKeyPressed(int keyCode);

	/// <summary>
	/// Sets the WindowShouldClose flag to true
	/// </summary>
	static void closeWindow();

	/// <summary>
	/// Sets width and height to the window's
	/// width and height in screen coordinates.
	/// </summary>
	static void getWindowSize(int& width, int& height);
};