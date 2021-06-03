#pragma once

#include "../engine/SceneObject.h"

class Sun : public Component {
public:
	Sun(SceneObject* obj);

	void update();
};

