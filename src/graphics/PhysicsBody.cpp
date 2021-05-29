#include "PhysicsBody.h"

void PhysicsBody::update() {
	kinematics.kinematicsUpdate();
	sceneObject->transform.rotation += kinematics.angularVelocity;
	float curRotation = sceneObject->transform.rotation;

	Vector2 velocity(cos(curRotation), sin(curRotation));
	velocity *= kinematics.forwardVelocity;

	sceneObject->transform.translation += velocity;
}

void KinematicProperties::kinematicsUpdate() {
	forwardVelocity = utils::clamp(forwardVelocity - utils::sign(forwardVelocity) * linearDrag + linearAcceleration, -terminalLinearVelocity, terminalLinearVelocity);
	angularVelocity = utils::clamp(angularVelocity - utils::sign(angularVelocity) * angularDrag + angularAcceleration, -terminalAngularVelocity, terminalAngularVelocity);
}