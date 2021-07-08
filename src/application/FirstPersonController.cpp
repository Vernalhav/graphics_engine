#include "FirstPersonController.h"
#include "../engine/Input.h"
#include "../misc/utils.h"

#include <glm/gtc/constants.hpp>


FirstPersonController::FirstPersonController(SceneObject* obj, bool isFreeCam, float ctrlSpeedModifier)
	: Component(obj), parentTransform(nullptr), mouseSensitivity(.001f),
	moveSpeed(20), maxVerticalAngle(glm::radians(80.0f)), isFreeCam(isFreeCam),
	ctrlSpeedModifier(ctrlSpeedModifier) { }

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

	glm::vec3 rotationDelta = { dy, -dx, 0 };
	glm::vec3 rotation = parentTransform->getRotation();

	// No need to multiply by deltaTime because dx, dy are already in pixels/frame
	rotation += mouseSensitivity * rotationDelta;
	rotation[0] = limitVerticalAngle(rotation[0], maxVerticalAngle);

	parentTransform->setRotation(rotation);
	
	glm::vec3 direction(0), forward, right, up;

	if (isFreeCam) {
		forward = parentTransform->getLocalDirection(Transform::forward);
		right = parentTransform->getLocalDirection(Transform::right);
		up = parentTransform->getLocalDirection(Transform::up);
	}
	else {
		forward = utils::projectToPlane(parentTransform->getLocalDirection(Transform::forward), Transform::up);
		right = utils::projectToPlane(parentTransform->getLocalDirection(Transform::right), Transform::up);
		up = Transform::up;
	}

	if (Input::isKeyPressed(KeyCode::W)) direction += forward;
	if (Input::isKeyPressed(KeyCode::A)) direction -= right;
	if (Input::isKeyPressed(KeyCode::S)) direction -= forward;
	if (Input::isKeyPressed(KeyCode::D)) direction += right;

	float ctrlSpeedModifier = 0.4f;
	float speedModifier = 1;
	if (!isFreeCam && Input::isKeyPressed(KeyCode::Space)) direction += up;
	if (!isFreeCam && Input::isKeyPressed(KeyCode::Shift)) direction -= up;
	if (!isFreeCam && Input::isKeyPressed(KeyCode::Ctrl)) speedModifier *= ctrlSpeedModifier;

	parentTransform->translate((float)Component::deltaTime * speedModifier * moveSpeed * direction);
}