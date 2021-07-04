#include "Input.h"
#include "Window.h"

#include <map>

const std::map<KeyCode, int> keyCodes{
	{ KeyCode::W, GLFW_KEY_W },
	{ KeyCode::A, GLFW_KEY_A },
	{ KeyCode::S, GLFW_KEY_S },
	{ KeyCode::D, GLFW_KEY_D }
};

bool Input::isKeyPressed(KeyCode keyCode) {
	return Window::activeWindow->isKeyPressed(keyCodes.at(keyCode));
}

void Input::getMouseDelta(double& dx, double& dy) {
	Window::activeWindow->getMouseDelta(dx, dy);
}
