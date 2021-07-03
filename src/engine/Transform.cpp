#include "Transform.h"
#include <glm/ext/matrix_transform.hpp>

Transform::Transform()
	: Transform({ 0, 0, 0 }, { 0, 0, 0 }, 1) { }

Transform::Transform(const glm::vec2& translation, float rotation, float scale)
	: translation(translation.x, translation.y, 0), rotation(0, 0, rotation), scale(scale) { }

Transform::Transform(const glm::vec3& translation, const glm::vec3& rotation, float scale)
	: translation(translation), rotation(rotation), scale(scale) { }

Transform::Transform(const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale)
	: translation(translation), rotation(rotation), scale(scale) { }

Transform Transform::operator+(const Transform& other) {
	return { translation + other.translation, rotation + other.rotation, scale * other.scale };
}

glm::mat4 Transform::getTransformMatrix() const {
	glm::mat4 transform(1);
	transform = glm::scale(transform, scale);
	transform = glm::rotate(transform, rotation.x, {1, 0, 0});
	transform = glm::rotate(transform, rotation.y, {0, 1, 0});
	transform = glm::rotate(transform, rotation.z, {0, 0, 1});
	transform = glm::translate(transform, translation);
	return transform;
}

Transform::operator glm::mat4() const {
	return getTransformMatrix();
}
