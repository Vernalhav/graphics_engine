#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include "Window.h"


Camera::Camera(SceneObject* obj)
	: Component(obj), screenWidth(0), screenHeight(0), zNear(0.5f), zFar(4000), fov(45) { }

void Camera::update() {
	Window::getActiveWindowSize(screenWidth, screenHeight);
}

float Camera::getFov() { return fov; }
float Camera::getNear() { return zNear; }
float Camera::getFar() { return zFar; }

void Camera::setFov(float fov) {
	this->fov = glm::clamp(fov, 10.0f, 170.0f);
}

void Camera::setNear(float near) {
	this->zNear = glm::max(near, 0.0f);
}

void Camera::setFar(float far) {
	this->zFar = glm::max(far, this->zNear + (float)1e-8);
};

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