#pragma once
#include "vectors.h"

struct Transform {
	Vector2 translation = { 0.0f, 0.0f };
	float rotation = 0;
	float scale = 1;

	Transform()
		: Transform({ 0, 0 }, 0, 1) { }

	Transform(const Vector2& translation, float rotation, float scale)
		: translation(translation), rotation(rotation), scale(scale) { }

	Transform operator+(const Transform& other) {
		return { translation + other.translation, rotation + other.rotation, scale + other.scale };
	}

	Transform& operator+=(const Transform& other) {
		translation += other.translation;
		rotation += other.rotation;
		scale += other.scale;
		return *this;
	}
};