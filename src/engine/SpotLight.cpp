#include "SpotLight.h"
#include "Scene.h"

SpotLight::SpotLight(SceneObject* obj, const glm::vec3& direction, float innerAngle, float outerAngleDiff, const glm::vec3& diffuse)
	: Light(obj, diffuse, 1),
	direction(direction),
	innerAngle(innerAngle),
	outerAngleDiff(outerAngleDiff) {
	
	Scene::getActiveScene()->addSpotLight(this);
}

glm::vec3 SpotLight::getDirection() {
	return direction;
}

float SpotLight::getInnerAngle() {
	return glm::radians(innerAngle);
}

float SpotLight::getOuterAngle() {
	return glm::radians(innerAngle + outerAngleDiff);
}

void SpotLight::setDirection(const glm::vec3& direction) {
	this->direction = direction;
}
