#include "Transform.h"
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>


Transform::Transform()
	: Transform({ 0, 0, 0 }, { 0, 0, 0 }, 1) { }

Transform::Transform(const glm::vec2& translation, float rotation, float scale)
	: _translation(translation.x, translation.y, 0), _rotation(0, 0, rotation), _scale(scale) { }

Transform::Transform(const glm::vec3& translation, const glm::vec3& rotation, float scale)
	: _translation(translation), _rotation(rotation), _scale(scale) { }

Transform::Transform(const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale)
	: _translation(translation), _rotation(rotation), _scale(scale) { }

glm::mat4 Transform::getTransformMatrix() const {
	glm::mat4 transform(1);
	transform = glm::translate(transform, _translation);
	transform = transform * glm::yawPitchRoll(_rotation.y, _rotation.x, _rotation.z);
	transform = glm::scale(transform, _scale);
	return transform;
}

glm::vec3 Transform::getLocalForward() {
	return getLocalDirection(Transform::forward);
}

glm::vec3 Transform::getLocalDirection(const glm::vec4& direction) {
	return glm::normalize(glm::yawPitchRoll(_rotation.y, _rotation.x, _rotation.z) * direction);
}

glm::vec3 Transform::getLocalDirection(const glm::vec3& direction) {
	glm::vec4 homogeneousDir = glm::vec4(direction, 0);
	return getLocalDirection(homogeneousDir);
}

void Transform::translate(const glm::vec3& translation) {
	_translation += translation;
}

void Transform::rotate(const glm::vec3& rotation) {
	_rotation = glm::mod(_rotation + rotation, glm::two_pi<float>());
}

void Transform::scale(float scale) {
	_scale *= scale;
}

void Transform::setTranslation(glm::vec3 translation) {
	_translation = translation;
}

void Transform::setRotation(glm::vec3 rotation) {
	_rotation = glm::mod(rotation, glm::two_pi<float>());
}

void Transform::setScale(float scale) {
	_scale = glm::vec3(scale);
}

glm::vec3 Transform::getTranslation() const {
	return _translation;
}

glm::vec3 Transform::getRotation() const {
	return _rotation;
}

glm::vec3 Transform::getScale() const {
	return _scale;
}

Transform::operator glm::mat4() const {
	return getTransformMatrix();
}
