#include "PointLight.h"
#include "Scene.h"

void PointLight::updateAttenuationCoefficients() {
	attenuationCoefficients = { 1, 0, (attenuationAtRadius - 1)/(radius * radius) };
}

PointLight::PointLight(SceneObject* obj, float radius, int attenuationAtRadius, const glm::vec3& diffuse)
	: Component(obj), radius(radius), attenuationAtRadius(attenuationAtRadius), diffuse(diffuse), attenuationCoefficients(1) {
	updateAttenuationCoefficients();
	
	Scene::getActiveScene()->addPointLight(this);
}

void PointLight::setRadius(float _radius) {
	radius = _radius;
	updateAttenuationCoefficients();
}

void PointLight::setAttenuationAtRadius(int attenuation) {
	attenuationAtRadius = attenuation;
	updateAttenuationCoefficients();
}

glm::vec3 PointLight::getDiffuseColor() {
	return diffuse;
}

glm::vec3 PointLight::getAttenuationCoefficients() {
	return attenuationCoefficients;
}

glm::vec3 PointLight::getPosition() {
	return sceneObject->getGlobalTransform()* glm::vec4(0, 0, 0, 1);
}
