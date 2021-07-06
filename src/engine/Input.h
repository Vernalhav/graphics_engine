#pragma once
#include "Window.h"


class KeyPressListener;
class MouseButtonListener;
class MouseScrollListener;

enum class KeyCode {
	W, A, S, D, P, None
};

enum class MouseButton {
	Left, Right, Middle, None
};

enum class ActionState {
	Performed, Released, None
};

class Input {
private:
	friend class WindowCallbacks;
	static KeyCode convertKeyCode(int key);
	static MouseButton convertMouseButton(int button);
	static ActionState convertActionState(int action);

public:
	/// <summary>
	/// Returns whether or not the keyCode
	/// is pressed or not
	/// </summary>
	static bool isKeyPressed(KeyCode keyCode);

	/// <summary>
	/// Sets dx and dy to contain the mouse's
	/// delta in x and y screen coordinates between
	/// the current frame and previous frame.
	/// The deltas are not normalized.
	/// </summary>
	static void getMouseDelta(double& dx, double& dy);

	static void addKeyListener(KeyPressListener* listener);
	static void addMouseButtonListener(MouseButtonListener* listener);
	static void addScrollListener(MouseScrollListener* listener);

	static void removeKeyListener(KeyPressListener* listener);
	static void removeMouseButtonListener(MouseButtonListener* listener);
	static void removeScrollListener(MouseScrollListener* listener);
};