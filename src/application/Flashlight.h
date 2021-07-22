#pragma once
#include "../engine/SceneObject.h"
#include "../engine/SpotLight.h"

class Flashlight : public Component {
private:
	SpotLight* light;

public:
	Flashlight(SceneObject* obj, SpotLight* light);

	void update() override;
};

