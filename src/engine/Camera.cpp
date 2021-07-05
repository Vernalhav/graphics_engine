#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include "Window.h"


Camera::Camera(SceneObject* obj)
	: Component(obj), screenWidth(0), screenHeight(0), zNear(0.5f), zFar(200), fov(45) { }

Camera::~Camera() { }

void Camera::update() {
	Window::getActiveWindowSize(screenWidth, screenHeight);
}

glm::mat4 Camera::getViewMatrix() {
	glm::mat4 globalTransform = sceneObject->getGlobalTransform();

	glm::vec3 camPosition = globalTransform * glm::vec4({ 0, 0, 0, 1 });
	glm::vec3 lookDirection = glm::normalize(globalTransform * Transform::forward);
	glm::vec3 viewUp = glm::normalize(globalTransform * Transform::up);

	return glm::lookAt(camPosition, camPosition + lookDirection, viewUp);
}

glm::mat4 Camera::getOrtoghraphicMatrix() {
	// FIXME: adapt to screen resize
	return glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, zNear, zFar);
}

glm::mat4 Camera::getProjectionMatrix() {
	return glm::perspective(glm::radians(fov), screenWidth/(float)screenHeight, zNear, zFar);
}

glm::mat4 Camera::getViewProjectionMatrix() {
	glm::mat4 view = getViewMatrix();
	glm::mat4 projection = getProjectionMatrix();
	return projection * view;
}