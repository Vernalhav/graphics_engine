#include "Ghast.h"
#include <iostream>

#include "../misc/utils.h"


Ghast::Ghast(SceneObject* obj, float speed)
	: Component(obj), moveSpeed(speed) , time(0) { }

void Ghast::update() {
	time += (float)Component::deltaTime;
	if (time > 10) {
		time = 0;
		sceneObject->transform.setRotationY(utils::randRange(0.0f, 6.0f));
	}
	sceneObject->transform.translate( -moveSpeed * sceneObject->transform.getLocalForward() * (float)Component::deltaTime );
}
