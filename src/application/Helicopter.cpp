#include "../engine/Input.h"
#include "Helicopter.h"

#include <iostream>


constexpr float HELICOPTER_RADIUS = 1.5f;

Helicopter::Helicopter(SceneObject* obj, bool controllable)
    : Component(obj), controllable(controllable), pb(nullptr), maxScale(1), minScale(1) {  }


void Helicopter::start() {
    pb = sceneObject->getComponent<PhysicsBody>();
    if (pb != nullptr) {
        maxScale = pb->sceneObject->transform.scale.x * 3 / 2;
        minScale = pb->sceneObject->transform.scale.x / 2;
    }
    else {
        maxScale = 1;
        minScale = 1;
        std::cout << "Helicopter: WARNING: Helicopter does not have a PhysicsBody component!" << std::endl;
    }
}

void Helicopter::update() {
	if (!controllable || pb == nullptr) return;

    pb->kinematics.linearAcceleration = 0;
    pb->kinematics.angularAcceleration = 0;

    if (Input::isKeyPressed(GLFW_KEY_W)) {
        pb->kinematics.linearAcceleration = linearAcceleration;
    }

    if (Input::isKeyPressed(GLFW_KEY_A)) {
        pb->kinematics.angularAcceleration = angularAcceleration;
    }

    if (Input::isKeyPressed(GLFW_KEY_D)) {
        pb->kinematics.angularAcceleration = -angularAcceleration;
    }

    if (Input::isKeyPressed(GLFW_KEY_UP)) {
        pb->sceneObject->transform.scale = glm::vec3(std::min(pb->sceneObject->transform.scale.x +
            scaleVelocty * (float)Component::deltaTime, maxScale));
    }

    if (Input::isKeyPressed(GLFW_KEY_DOWN)) {
        pb->sceneObject->transform.scale = glm::vec3(std::max(pb->sceneObject->transform.scale.x -
            scaleVelocty * (float)Component::deltaTime, minScale));
    }

    if (abs(sceneObject->transform.translation.x) > HELICOPTER_RADIUS
        || abs(sceneObject->transform.translation.y) > HELICOPTER_RADIUS)
        Input::closeWindow();
}
