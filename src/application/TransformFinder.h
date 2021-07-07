#pragma once
#include "../engine/SceneObject.h"

class TransformFinder : public Component {
private:
	float sensitivity;
	float sensitivityModifier;

public:
	TransformFinder(SceneObject* obj);

	void update();
};

