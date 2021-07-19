#include "PointLight.h"


void PointLight::updateAttenuationCoefficients() {
	attenuationCoefficients = { 1, 0, (attenuationAtRadius - 1)/(radius * radius) };
}

PointLight::PointLight(SceneObject* obj, float radius, int attenuationAtRadius, const glm::vec3& diffuse)
	: Component(obj), radius(radius), attenuationAtRadius(attenuationAtRadius), diffuse(diffuse), attenuationCoefficients(1) {
	updateAttenuationCoefficients();
}

void PointLight::setRadius(float _radius) {
	radius = _radius;
	updateAttenuationCoefficients();
}

void PointLight::setAttenuationAtRadius(int attenuation) {
	attenuationAtRadius = attenuation;
	updateAttenuationCoefficients();
}
