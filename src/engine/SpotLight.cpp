#include "SpotLight.h"
#include "Scene.h"

SpotLight::SpotLight(SceneObject* obj, const glm::vec3& direction, float innerAngle, float outerAngleDiff, const glm::vec3& diffuse)
	: Component(obj),
	direction(direction),
	innerAngle(innerAngle),
	outerAngleDiff(outerAngleDiff),
	diffuse(diffuse) {
	
	Scene::getActiveScene()->addSpotLight(this);
}

glm::vec3 SpotLight::getDirection() {
	return direction;
}

glm::vec3 SpotLight::getPosition() {
	return sceneObject->getGlobalTransform() * glm::vec4(0, 0, 0, 1);
}

glm::vec3 SpotLight::getDiffuse() {
	return diffuse;
}

float SpotLight::getInnerAngle() {
	return glm::radians(innerAngle);
}

float SpotLight::getOuterAngle() {
	return glm::radians(innerAngle + outerAngleDiff);
}
