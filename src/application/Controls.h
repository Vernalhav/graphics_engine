#pragma once
#include "../engine/SceneObject.h"
#include "../engine/KeyPressListener.h"
#include "../engine/MouseScrollListener.h"
#include "../engine/Camera.h"
#include "../engine/AmbientLight.h"
#include "../engine/Scene.h"

class Controls : public Component, public KeyPressListener, public MouseScrollListener {
private:
	Camera* cam;
	AmbientLight* light;
	float sensitivity;

	bool lightingEnabled = true;

public:
	Controls(SceneObject* obj, Camera* cam = nullptr, AmbientLight* light = nullptr);

	// Inherited via KeyPressListener
	virtual void onKeyPressed(KeyCode key, ActionState state) override;

	// Inherited via MouseScrollListener
	virtual void onMouseScroll(float y) override;
};

