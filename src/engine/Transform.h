#pragma once
#include <glm/glm.hpp>


class Transform {
	glm::vec3 _translation;
	glm::vec3 _rotation;
	glm::vec3 _scale;

public:
	constexpr static glm::vec4 forward = { 0, 0, -1, 0 };
	constexpr static glm::vec4 up = { 0, 1, 0, 0 };
	constexpr static glm::vec4 right = { 1, 0, 0, 0 };

	Transform();

	// 2D Compatibility constructor (z-axis rotation)
	Transform(const glm::vec2& translation, float rotation, float scale);

	// Uniform scale constructor
	Transform(const glm::vec3& translation, const glm::vec3& rotation, float scale);

	// Non-uniform scale constructor
	Transform(const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale);

	/// <summary>
	/// Returns unit vector representing
	/// the local (non-hierarchical)
	/// forward vector.
	/// </summary>
	glm::vec3 getLocalForward();
	glm::vec3 getLocalDirection(const glm::vec3& direction);
	glm::vec3 getLocalDirection(const glm::vec4& direction);
	
	// The three functions below increment the
	// specified value by the provided amount.
	void translate(const glm::vec3& translation);
	void rotate(const glm::vec3& rotation);
	void scale(float scale);

	void setTranslation(glm::vec3 translation);
	void setRotation(glm::vec3 rotation);
	void setScale(float scale);

	void setRotationX(float theta);
	void setRotationY(float theta);
	void setRotationZ(float theta);

	glm::vec3 getTranslation() const;
	glm::vec3 getRotation() const;
	glm::vec3 getScale() const;

	// Implicit conversion from Transform to transform matrix. Calls getTransformMatrix
	operator glm::mat4() const;
	glm::mat4 getTransformMatrix() const;
};