#pragma once

#include "vectors.h"
#include "Transform.h"

struct PhysicsBody {
	float forwardVelocity;
	float angularVelocity;

	PhysicsBody() : PhysicsBody(0, 0) { }

	PhysicsBody(float forwardVelocity, float angularVelocity)
		: forwardVelocity(forwardVelocity), angularVelocity(angularVelocity) { }

	void updateTransform(Transform& t) {
		t.rotation += angularVelocity;
		float curRotation = t.rotation;

		Vector2 velocity(cos(curRotation), sin(curRotation));
		velocity *= forwardVelocity;

		t.translation += velocity;
	}
};