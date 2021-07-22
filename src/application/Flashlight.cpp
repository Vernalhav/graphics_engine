#include "Flashlight.h"

Flashlight::Flashlight(SceneObject* obj, SpotLight* light)
	: Component(obj), light(light) { }

void Flashlight::update() {
	glm::vec3 forward = sceneObject->transform.getLocalForward();
	light->setDirection(forward);
}
