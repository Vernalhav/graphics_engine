#pragma once

#include "SceneObject.h"

class Camera : public Component {
private:
	
public:
	Camera(SceneObject* parent);
	~Camera();
};

