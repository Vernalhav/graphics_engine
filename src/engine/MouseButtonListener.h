#pragma once

enum class MouseButton;
enum class ActionState;

class MouseButtonListener {
public:
	virtual void onMouseButtonClicked(MouseButton button, ActionState state) = 0;
};
