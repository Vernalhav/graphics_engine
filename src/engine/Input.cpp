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
	if (Window::activeWindow == nullptr) return false;
	return Window::activeWindow->isKeyPressed(keyCodes.at(keyCode));
}

void Input::getMouseDelta(double& dx, double& dy) {
	if (Window::activeWindow == nullptr) {
		dx = 0;
		dy = 0;
		return;
	}
	Window::activeWindow->getMouseDelta(dx, dy);
}
