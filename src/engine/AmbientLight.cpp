#include "AmbientLight.h"
#include "Scene.h"

AmbientLight::AmbientLight(SceneObject* obj, float intensity, const glm::vec3& diffuse)
	: Component(obj), diffuse(diffuse), intensity(intensity) {
	Scene::getActiveScene()->setAmbientLight(this);
}

glm::vec3 AmbientLight::getDiffuseColor() {
	return diffuse;
}

float AmbientLight::getIntensity() {
	return intensity;
}

void AmbientLight::setDiffuseColor(const glm::vec3& diffuse) {
	this->diffuse = diffuse;
}

void AmbientLight::setIntensity(float intensity) {
	this->intensity = intensity;
}
