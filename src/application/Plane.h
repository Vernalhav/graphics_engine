#pragma once

#include "../engine/SceneObject.h"


class Plane : public Component {
public:
	Plane(SceneObject* obj);

	void update();
};

