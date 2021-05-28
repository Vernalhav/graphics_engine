#pragma once
#include "../graphics/Component.h"

class Cloud : public Component {
public:
	Cloud(SceneObject* obj);
	
	void update();
};

