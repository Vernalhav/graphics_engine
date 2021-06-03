#include "Sun.h"
#include "../misc/utils.h"

constexpr float SUN_THRESHOLD = -1.5f;

Sun::Sun(SceneObject* obj) : Component(obj) { }

void Sun::update() {
	if (sceneObject->transform.translation.y < SUN_THRESHOLD) {
		sceneObject->transform.translation.y = -SUN_THRESHOLD;
	}
}
