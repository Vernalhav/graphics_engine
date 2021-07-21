#include "Controls.h"
#include "../engine/Scene.h"
#include "../engine/Input.h"
#include <iostream>

Controls::Controls(SceneObject* obj, Camera* cam, AmbientLight* light)
	: Component(obj), cam(cam), light(light), sensitivity(2) {
	Input::addKeyListener(this);
	Input::addScrollListener(this);
}

void Controls::onKeyPressed(KeyCode key, ActionState state) {
	if (key == KeyCode::M && state == ActionState::Performed) {
		Scene::getActiveScene()->toggleDrawMode();
	}

	if (key == KeyCode::L && state == ActionState::Performed) {
		lightingEnabled = !lightingEnabled;
		Scene::getActiveScene()->setLightingEnabled(lightingEnabled);
	}

	if (light != nullptr) {
		float lightIntensity = light->getIntensity();
		if (key == KeyCode::U && state == ActionState::Performed)
			lightIntensity -= 0.1f;

		if (key == KeyCode::P && state == ActionState::Performed)
			lightIntensity += 0.1f;

		light->setIntensity(std::clamp(lightIntensity, 0.0f, 1.0f));
	}
}

void Controls::onMouseScroll(float y) {
	if (cam == nullptr) return;
	cam->setFov( cam->getFov() - y * sensitivity );
}
