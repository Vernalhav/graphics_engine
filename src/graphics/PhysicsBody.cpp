#include <iostream>

#include "PhysicsBody.h"


void PhysicsBody::update() {
	kinematics.kinematicsUpdate();
	std::cout << sceneObject->getName() << ": " << kinematics.linearVelocity << std::endl;
	sceneObject->transform.rotation += kinematics.angularVelocity * (float)Component::deltaTime;

	float curRotation = sceneObject->transform.rotation;
	Vector2 velocity(cos(curRotation), sin(curRotation));
	velocity *= kinematics.linearVelocity;

	sceneObject->transform.translation += velocity * (float)Component::deltaTime;
}

void KinematicProperties::kinematicsUpdate() {
	linearVelocity = utils::clamp(linearVelocity - utils::sign(linearVelocity) * linearDrag + linearAcceleration, -terminalLinearVelocity, terminalLinearVelocity);
	angularVelocity = utils::clamp(angularVelocity - utils::sign(angularVelocity) * angularDrag + angularAcceleration, -terminalAngularVelocity, terminalAngularVelocity);

	if (abs(linearVelocity) <= linearDrag) linearVelocity = 0;
	if (abs(angularVelocity) <= angularDrag) angularVelocity = 0;
}