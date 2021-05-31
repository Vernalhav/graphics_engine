#pragma once
#include "../engine/SceneObject.h"

class Cloud : public Component {
public:
	Cloud(SceneObject* obj);
	
	void update();
};

