#include "Cloud.h"
#include "../misc/utils.h"


constexpr float CLOUD_THRESHOLD = 1.2f;

Cloud::Cloud(SceneObject* obj) : Component(obj) { }

void Cloud::update() {
	if (sceneObject->transform.translation.x > CLOUD_THRESHOLD) {
		sceneObject->transform.translation.x = -CLOUD_THRESHOLD;
		sceneObject->transform.translation.y = utils::randRange(-0.9f, 0.9f);
	}
}
