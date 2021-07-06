#include "Controls.h"
#include "../engine/Scene.h"
#include "../engine/Input.h"
#include <iostream>

Controls::Controls(SceneObject* obj, Camera* cam) : Component(obj), cam(cam), sensitivity(2) {
	Input::addKeyListener(this);
	Input::addScrollListener(this);
}

void Controls::onKeyPressed(KeyCode key, ActionState state) {
	if (key == KeyCode::P && state == ActionState::Performed) {
		Scene::getActiveScene()->toggleDrawMode();
	}
}

void Controls::onMouseScroll(float y) {
	if (cam == nullptr) return;
	cam->setFov( cam->getFov() - y * sensitivity );
}
