#include "Input.h"

#include <map>


template<typename T, typename U>
constexpr const std::map<U, T> invertMap(const std::map<T, U> inputMap) {
	std::map<U, T> outputMap;

	for (auto& pair : inputMap) {
		outputMap[pair.second] = pair.first;
	}

	return outputMap;
}

const std::map<KeyCode, int> keyCodes = {
	{ KeyCode::W, GLFW_KEY_W },
	{ KeyCode::A, GLFW_KEY_A },
	{ KeyCode::S, GLFW_KEY_S },
	{ KeyCode::D, GLFW_KEY_D },
	{ KeyCode::P, GLFW_KEY_P },
	{ KeyCode::Up, GLFW_KEY_UP },
	{ KeyCode::Down, GLFW_KEY_DOWN },
	{ KeyCode::Left, GLFW_KEY_LEFT },
	{ KeyCode::Right, GLFW_KEY_RIGHT },
	{ KeyCode::Space, GLFW_KEY_SPACE },
	{ KeyCode::Ctrl, GLFW_KEY_LEFT_CONTROL },
	{ KeyCode::Shift, GLFW_KEY_LEFT_SHIFT }
};

const std::map<MouseButton, int> mouseButtonCodes = {
	{ MouseButton::Left, GLFW_MOUSE_BUTTON_1 },
	{ MouseButton::Right, GLFW_MOUSE_BUTTON_2 },
	{ MouseButton::Middle, GLFW_MOUSE_BUTTON_3 }
};

const std::map<ActionState, int> actionStateCodes = {
	{ ActionState::Performed, GLFW_PRESS },
	{ ActionState::Released, GLFW_RELEASE }
};

const std::map<int, KeyCode> keyCodesInv = invertMap(keyCodes);
const std::map<int, MouseButton> mouseButtonCodesInv = invertMap(mouseButtonCodes);
const std::map<int, ActionState> actionsStateInv = invertMap(actionStateCodes);

KeyCode Input::convertKeyCode(int key) {
	if (!keyCodesInv.count(key)) return KeyCode::None;
	return keyCodesInv.at(key);
}

MouseButton Input::convertMouseButton(int button) {
	if (!mouseButtonCodesInv.count(button)) return MouseButton::None;
	return mouseButtonCodesInv.at(button);
}

ActionState Input::convertActionState(int action) {
	if (!actionsStateInv.count(action)) return ActionState::None;
	return actionsStateInv.at(action);
}

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

void Input::addKeyListener(KeyPressListener* listener) {
	Window::activeWindow->addKeyListener(listener);
}

void Input::addMouseButtonListener(MouseButtonListener* listener) {
	Window::activeWindow->addMouseButtonListener(listener);
}

void Input::addScrollListener(MouseScrollListener* listener) {
	Window::activeWindow->addScrollListener(listener);
}

void Input::removeKeyListener(KeyPressListener* listener) {
	Window::activeWindow->removeKeyListener(listener);
}

void Input::removeMouseButtonListener(MouseButtonListener* listener) {
	Window::activeWindow->removeMouseButtonListener(listener);
}

void Input::removeScrollListener(MouseScrollListener* listener) {
	Window::activeWindow->removeScrollListener(listener);
}