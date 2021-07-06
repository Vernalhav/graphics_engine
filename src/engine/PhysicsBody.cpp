#include "PhysicsBody.h"

PhysicsBody::PhysicsBody(SceneObject* obj)
	: Component(obj), linearVelocity(0), angularVelocity(0) {  }

PhysicsBody::PhysicsBody(SceneObject* obj, const glm::vec3& linearVelocity, const glm::vec3& angularVelocity) 
	: Component(obj), linearVelocity(linearVelocity), angularVelocity(angularVelocity) { }

void PhysicsBody::update() {
	sceneObject->transform.rotate(angularVelocity * (float)Component::deltaTime);
	sceneObject->transform.translate(linearVelocity * (float)Component::deltaTime);
}
