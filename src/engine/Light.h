#pragma once
#include "SceneObject.h"

class Light : public Component {
protected:
	glm::vec3 diffuse;
	float intensity;
	Light(SceneObject* obj, const glm::vec3& diffuse = glm::vec3(1), float intensity = 1);

public:
	glm::vec3 getPosition();
	float getIntensity();
	glm::vec3 getDiffuse();

	void setIntensity(float intensity);
	void setDiffuse(const glm::vec3& diffuse);
};

