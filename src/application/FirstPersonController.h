#pragma once
#include "../engine/SceneObject.h"

class FirstPersonController : public Component {
private:
	Transform* parentTransform;

	float moveSpeed;			// Units per second
	float mouseSensitivity;		// Radians per frame
	float maxVerticalAngle;		// In radians
	float ctrlSpeedModifier;
	bool isFreeCam;				// Whether to lock movement in XZ plane

public:	
	FirstPersonController(SceneObject* obj, bool isFreeCam = false, float ctrlSpeedModifier = 2);

	void start();
	void update();
};