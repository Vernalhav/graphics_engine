#pragma once
#include "../engine/SceneObject.h"

class Ghast : public Component {
private:
	float moveSpeed;
	float time;

public:
	Ghast(SceneObject* obj, float moveSpeed = 1.0f);
	
	void update() override;
};

