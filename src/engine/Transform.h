#pragma once
#include <glm/glm.hpp>

struct Transform {
	glm::vec3 translation;
	glm::vec3 rotation;
	glm::vec3 scale;

	Transform();

	// 2D Compatibility constructor (z-axis rotation)
	Transform(const glm::vec2& translation, float rotation, float scale);

	// Uniform scale constructor
	Transform(const glm::vec3& translation, const glm::vec3& rotation, float scale);

	// Non-uniform scale constructor
	Transform(const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale);

	glm::mat4 getTransformMatrix() const;

	Transform operator+(const Transform& other);

	Transform& operator+=(const Transform& other);

	operator glm::mat4() const;
};