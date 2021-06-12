#include "PhysicsBody.h"


void PhysicsBody::update() {
	kinematics.kinematicsUpdate();
	sceneObject->transform.rotation += kinematics.angularVelocity * (float)Component::deltaTime;

	float curRotation = sceneObject->transform.rotation.z;
	glm::vec2 velocity(cos(curRotation), sin(curRotation));
	velocity *= kinematics.linearVelocity;

	sceneObject->transform.translation += glm::vec3(velocity * (float)Component::deltaTime, 0);
}

void KinematicProperties::kinematicsUpdate() {
	linearVelocity = utils::clamp(linearVelocity - utils::sign(linearVelocity) * linearDrag + linearAcceleration,
		-terminalLinearVelocity, terminalLinearVelocity);
	
	angularVelocity = utils::clamp(angularVelocity - utils::sign(angularVelocity) * angularDrag + angularAcceleration,
		-terminalAngularVelocity, terminalAngularVelocity);

	// FIXME: Gambiarra
	if (abs(linearVelocity) <= linearDrag) linearVelocity = 0;
	if (abs(angularVelocity) <= angularDrag) angularVelocity = 0;
}