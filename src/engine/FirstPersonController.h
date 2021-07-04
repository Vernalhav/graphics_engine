#pragma once
#include "SceneObject.h"

class FirstPersonController : public Component {
private:
	Transform* parentTransform;

	float moveSpeed;
	float mouseSensitivity;
	float maxVerticalAngle;
public:	
	FirstPersonController(SceneObject* obj);
	~FirstPersonController();

	void start();
	void update();
};