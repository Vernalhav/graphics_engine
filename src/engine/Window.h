#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <string>
#include <vector>

#include "Input.h"
#include "SceneObject.h"

#include "KeyPressListener.h"
#include "MouseButtonListener.h"
#include "MouseScrollListener.h"

enum class KeyCode;
enum class ActionState;
enum class MouseButton;

class Window;

using KeyCallbackFunction = void (KeyPressListener::*)(Window*, KeyCode, ActionState);
using MouseCallbackFunction = void (MouseButtonListener::*)(Window*, MouseButton, ActionState);
using ScrollCallbackFunction = void (MouseScrollListener::*)(Window*, MouseButton, ActionState);

class Window {
private:
	friend class Input;
	friend class WindowCallbacks;
	static Window* activeWindow;
	
	GLFWwindow* window;
	double lastX;
	double lastY;
	double dx;
	double dy;

	std::vector<KeyPressListener*> keyPressListeners;
	std::vector<MouseButtonListener*> mouseButtonListeners;
	std::vector<MouseScrollListener*> scrollListeners;

	void captureMouseCursor();
	void releaseMouseCursor();
	void setActive();

	void addKeyListener(KeyPressListener* listener);
	void addMouseButtonListener(MouseButtonListener* listener);
	void addScrollListener(MouseScrollListener* listener);
	void removeKeyListener(KeyPressListener* listener);
	void removeMouseButtonListener(MouseButtonListener* listener);
	void removeScrollListener(MouseScrollListener* listener);

	void onKeyPress(KeyCode key, ActionState state);
	void onMouseButtonClick(MouseButton button, ActionState state);
	void onScroll(float amount);

public:
	Window(int width = 800, int height = 800, const std::string& name = "OpenGL Window");
	~Window();

	bool shouldClose();
	void show();
	void close();
	void display();

	/// <summary>
	/// Sets width and height parameters to
	/// contain the window's width and height
	/// in pixels, not in screen coordinates.
	/// </summary>
	void getWindowSize(int& width, int& height);
	
	/// <summary>
	/// Sets dx and dy to contain the mouse's
	/// delta in x and y screen coordinates between
	/// the current frame and previous frame.
	/// The deltas are not normalized.
	/// </summary>
	void getMouseDelta(double& dx, double& dy);

	bool isKeyPressed(int KeyCode);
	void pollEvents();

	static void clearBuffers();
	static void setColor(const glm::vec3& color);
	static double getDeltaTime();
	static void getActiveWindowSize(int& width, int& height);

	static void terminate();
};