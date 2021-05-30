#pragma once
#include "../graphics/SceneObject.h"

class Cloud : public Component {
public:
	Cloud(SceneObject* obj);
	
	void update();
};

