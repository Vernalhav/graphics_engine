#pragma once

#include "../math/vectors.h"
#include "Component.h"

class PhysicsBody: public Component {
public:
	float forwardVelocity;
	float angularVelocity;

	PhysicsBody(SceneObject* obj) : PhysicsBody(obj, 0, 0) { }

	PhysicsBody(SceneObject* obj, float forwardVelocity, float angularVelocity)
		: Component(obj), forwardVelocity(forwardVelocity), angularVelocity(angularVelocity) { }

	void update() {
		sceneObject->transform.rotation += angularVelocity;
		float curRotation = sceneObject->transform.rotation;

		Vector2 velocity(cos(curRotation), sin(curRotation));
		velocity *= forwardVelocity;

		sceneObject->transform.translation += velocity;
	}
};