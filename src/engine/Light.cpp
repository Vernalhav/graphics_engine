#include "Light.h"

Light::Light(SceneObject* obj, const glm::vec3& diffuse, float intensity)
	: Component(obj), diffuse(diffuse), intensity(intensity) { }

glm::vec3 Light::getPosition() {
	return sceneObject->getGlobalTransform() * glm::vec4(0, 0, 0, 1);
}

float Light::getIntensity() {
	return intensity;
}

glm::vec3 Light::getDiffuse() {
	return diffuse;
}

void Light::setIntensity(float intensity) {
	this->intensity = intensity;
}

void Light::setDiffuse(const glm::vec3& diffuse) {
	this->diffuse = diffuse;
}
