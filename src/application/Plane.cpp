#include "Plane.h"
#include "../misc/utils.h"

constexpr float PLANE_THRESHOLD = 1.5f;

Plane::Plane(SceneObject* obj) : Component(obj) { }

void Plane::update() {
	if (sceneObject->transform.translation.y >= PLANE_THRESHOLD) {
		sceneObject->transform.translation.y = -PLANE_THRESHOLD;
		sceneObject->transform.translation.x = utils::randRange(-0.9f, 0.9f);
		sceneObject->transform.scale = utils::randRange(0.1f, 0.25f);
	}
}
