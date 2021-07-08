#pragma once
#include "../engine/SceneObject.h"

class SinMovement : public Component {
private:
	float amplitude;
	float frequency;
	glm::vec3 direction;
	float time;

public:
	SinMovement(SceneObject* obj, float amplitude = 1, float frequency = 1e-2, const glm::vec3& direction = Transform::up);

	void update() override;
};

