#pragma once

enum class KeyCode;
enum class ActionState;

class KeyPressListener {
public:
	virtual void onKeyPressed(KeyCode key, ActionState action) = 0;
};

