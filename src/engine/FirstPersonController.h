#pragma once
#include "SceneObject.h"

class FirstPersonController : public Component {
private:
	Transform* parentTransform;

	float moveSpeed;			// Units per second
	float mouseSensitivity;		// Radians per frame
	float maxVerticalAngle;		// In radians

public:	
	FirstPersonController(SceneObject* obj);
	~FirstPersonController();

	void start();
	void update();
};