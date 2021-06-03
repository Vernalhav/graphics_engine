#pragma once

#include "../engine/SceneObject.h"

class Sun : public Component {
private:
	Vector3 colorStart, colorEnd;
	unsigned int frameNumber;
	float initialScale;

public:
	Sun(SceneObject* obj, const Vector3& colorStart, const Vector3& colorEnd);

	void start();

	void update();
};

