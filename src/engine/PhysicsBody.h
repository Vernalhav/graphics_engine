#pragma once
#include "SceneObject.h"

class PhysicsBody : public Component {
private:
	glm::vec3 linearVelocity;
	glm::vec3 angularVelocity;

public:
	PhysicsBody(SceneObject* obj);

	PhysicsBody(SceneObject* obj, const glm::vec3& linearVelocity, const glm::vec3& angularVelocity);

	void update();
};

