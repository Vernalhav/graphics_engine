#pragma once

#include "../engine/SceneObject.h"
#include "../engine/PhysicsBody.h"

class Helicopter : public Component {
private:
	PhysicsBody* pb;
	bool controllable;

	float linearAcceleration = 0.005f;
	float angularAcceleration = 0.05f;
	float scaleVelocty = 0.5f;

	float maxScale;
	float minScale;

public:
	Helicopter(SceneObject* obj, bool controllable = true);

	void start();

	void update();
};

