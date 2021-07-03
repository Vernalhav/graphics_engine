#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <string>

class Window {
private:
	static Window* activeWindow;
	
	friend class Input;
	GLFWwindow* window;

public:
	Window(int width = 800, int height = 800, const std::string& name = "OpenGL Window");
	~Window();

	void captureMouseCursor();
	void releaseMouseCursor();
	void setActive();

	bool shouldClose();
	void show();
	void close();
	void display();
	void getWindowSize(int& width, int& height);

	bool isKeyPressed(int keyCode);

	static void pollEvents();
	static void clearBuffers();
	static void setColor(const glm::vec3& color);
	static double getDeltaTime();
	static void getActiveWindowSize(int& width, int& height);

	static void terminate();
};