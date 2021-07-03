#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <string>

class Window {
private:
	GLFWwindow* window;
	bool isFocused;

	friend class Input;

	void captureMouseCursor();

public:
	Window(int width = 800, int height = 800, const std::string& name = "OpenGL Window");
	~Window();

	void releaseMouseCursor();
	void setActive();

	bool shouldClose();
	void show();
	void close();
	void display();

	static void pollEvents();
	static void clearBuffers();
	static void setColor(const glm::vec3& color);
	static double getDeltaTime();

	static void terminate();
};