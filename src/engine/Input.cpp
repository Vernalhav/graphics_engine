#include "Input.h"
#include "Window.h"

bool Input::isKeyPressed(int keyCode) {
	return Window::activeWindow->isKeyPressed(keyCode);
}