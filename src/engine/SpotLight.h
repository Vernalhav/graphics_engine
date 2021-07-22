#pragma once
#include "SceneObject.h"

class SpotLight : public Component {
private:
	glm::vec3 direction;
	glm::vec3 diffuse;

	float innerAngle;
	float outerAngleDiff;		// Outer angle will be innerAngle + outerAngleDiff

public:
	SpotLight(SceneObject* obj,
				const glm::vec3& direction,
				float innerAngle = 10.0f,
				float outerAngleDiff = 3.0f,
				const glm::vec3& diffuse = glm::vec3(1));

	glm::vec3 getDirection();
	glm::vec3 getPosition();
	glm::vec3 getDiffuse();
	float getInnerAngle();
	float getOuterAngle();

	void setDirection(const glm::vec3& direction);
};

