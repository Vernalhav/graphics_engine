#include "AmbientLight.h"

AmbientLight::AmbientLight(SceneObject* obj, float intensity, const glm::vec3& diffuse)
	: Component(obj), diffuse(diffuse), intensity(intensity) { }

glm::vec3 AmbientLight::getDiffuseColor() {
	return diffuse;
}

float AmbientLight::getIntensity() {
	return intensity;
}
