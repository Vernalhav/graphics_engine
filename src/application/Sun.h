#pragma once

#include "../engine/SceneObject.h"

class Sun : public Component {
private:
	glm::vec3 colorStart, colorEnd;
	unsigned int frameNumber;
	float initialScale;

public:
	Sun(SceneObject* obj, const glm::vec3& colorStart, const glm::vec3& colorEnd);

	void start();

	void update();
};

