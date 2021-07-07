#pragma once
#include "../engine/SceneObject.h"

class Confiner : public Component {
private:
	glm::vec2 xBounds;
	glm::vec2 yBounds;
	glm::vec2 zBounds;

public:
	Confiner(SceneObject* obj, const glm::vec2& xBounds, const glm::vec2& yBounds, const glm::vec2& zBounds);

	void update() override;
};

