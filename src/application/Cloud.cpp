#include "Cloud.h"
#include "../misc/utils.h"

Cloud::Cloud(SceneObject* obj) : Component(obj) { }

void Cloud::update() {
	if (sceneObject->transform.translation.x > 1.2) {
		sceneObject->transform.translation.x = -1.2f;
		sceneObject->transform.translation.y = utils::randRange(-0.8f, 0.8f);
	}
}
