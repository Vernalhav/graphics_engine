#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include "Input.h"


Camera::Camera(SceneObject* obj)
	: Component(obj), screenWidth(0), screenHeight(0), zNear(0.1f), zFar(100), fov(45) { }

Camera::~Camera() { }

void Camera::update() {
	Input::getWindowSize(screenWidth, screenHeight);
}

glm::mat4 Camera::getViewMatrix() {
	glm::mat4 globalTransform = sceneObject->getGlobalTransform();

	glm::vec3 camPosition = globalTransform * glm::vec4({ 0, 0, 0, 1 });
	glm::vec3 lookDirection = glm::normalize(globalTransform * glm::vec4({ 0, 0, -1, 0 }));
	glm::vec3 viewUp = glm::normalize(globalTransform * glm::vec4({ 0, 1, 0, 0 }));

	return glm::lookAt(camPosition, camPosition + lookDirection, viewUp);
}

glm::mat4 Camera::getProjectionMatrix() {
	return glm::perspectiveFov(fov, (float)screenWidth, (float)screenHeight, zNear, zFar);
}

glm::mat4 Camera::getViewProjectionMatrix() {
	glm::mat4 view = getViewMatrix();
	glm::mat4 projection = getProjectionMatrix();
	return projection * view;
}