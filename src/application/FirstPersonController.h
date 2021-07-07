#pragma once
#include "../engine/SceneObject.h"

class FirstPersonController : public Component {
private:
	Transform* parentTransform;

	float moveSpeed;			// Units per second
	float mouseSensitivity;		// Radians per frame
	float maxVerticalAngle;		// In radians
	bool isFreeCam;

public:	
	FirstPersonController(SceneObject* obj, bool isFreeCam = false);

	void start();
	void update();
};