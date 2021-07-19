#pragma once
#include "SceneObject.h"

class AmbientLight : public Component {
private:
	glm::vec3 diffuse;
	float intensity;

public:
	AmbientLight(SceneObject* obj, float intensity = 1, const glm::vec3& diffuse = glm::vec3(1));

	glm::vec3 getDiffuseColor();
	float getIntensity();
};
