#pragma once
#include "../engine/SceneObject.h"
#include "../engine/KeyPressListener.h"
#include "../engine/MouseScrollListener.h"
#include "../engine/Camera.h"

class Controls : public Component, public KeyPressListener, public MouseScrollListener {
private:
	Camera* cam;
	float sensitivity;

public:
	Controls(SceneObject* obj, Camera* cam = nullptr);

	// Inherited via KeyPressListener
	virtual void onKeyPressed(KeyCode key, ActionState state) override;

	// Inherited via MouseScrollListener
	virtual void onMouseScroll(float y) override;
};

