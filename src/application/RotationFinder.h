#pragma once
#include "../engine/SceneObject.h"

class RotationFinder : public Component {
private:
	float sensitivity;
	float sensitivityModifier;

public:
	RotationFinder(SceneObject* obj);

	void update() override;
};

