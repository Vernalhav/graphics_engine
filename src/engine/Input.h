#pragma once

enum class KeyCode {
	W, A, S, D
};

class Input {
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
};