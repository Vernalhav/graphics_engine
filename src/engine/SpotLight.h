#pragma once
#include "Light.h"

class SpotLight : public Light {
private:
	glm::vec3 direction;

	float innerAngle;
	float outerAngleDiff;		// Outer angle will be innerAngle + outerAngleDiff

public:
	SpotLight(SceneObject* obj,
				const glm::vec3& direction,
				float innerAngle = 10.0f,
				float outerAngleDiff = 3.0f,
				const glm::vec3& diffuse = glm::vec3(1));

	glm::vec3 getDirection();
	float getInnerAngle();
	float getOuterAngle();

	void setDirection(const glm::vec3& direction);
};

