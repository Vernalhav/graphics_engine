#include "FirstPersonController.h"
#include "Input.h"

#include <glm/gtc/constants.hpp>

FirstPersonController::FirstPersonController(SceneObject* obj)
	: Component(obj), parentTransform(nullptr), mouseSensitivity(.7f),
	moveSpeed(20), maxVerticalAngle(glm::radians(60.0f)) { }

FirstPersonController::~FirstPersonController() { }

void FirstPersonController::start() {
	parentTransform = &(sceneObject->transform);
}

float limitVerticalAngle(float rotation, float maxAngle) {
	float lowerBound = glm::two_pi<float>() - maxAngle;
	if (rotation < maxAngle || rotation > lowerBound)
		return rotation;

	return (glm::abs(rotation - maxAngle) < glm::abs(lowerBound - rotation)) ? maxAngle : lowerBound;
}

void FirstPersonController::update() {
	double dx, dy;
	Input::getMouseDelta(dx, dy);

	glm::vec3 rotationDiff = { dy, -dx, 0 };
	glm::vec3 rotation = parentTransform->getRotation();

	rotation += (float)Component::deltaTime * mouseSensitivity * rotationDiff;
	rotation[0] = limitVerticalAngle(rotation[0], maxVerticalAngle);

	parentTransform->setRotation(rotation);
	
	glm::vec3 direction(0);
	glm::vec3 forward = parentTransform->getLocalDirection(Transform::forward);
	glm::vec3 right= parentTransform->getLocalDirection(Transform::right);

	if (Input::isKeyPressed(KeyCode::W)) direction += forward;
	if (Input::isKeyPressed(KeyCode::A)) direction -= right;
	if (Input::isKeyPressed(KeyCode::S)) direction -= forward;
	if (Input::isKeyPressed(KeyCode::D)) direction += right;

	parentTransform->translate((float)Component::deltaTime * moveSpeed * direction);
}