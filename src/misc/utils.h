#pragma once

#include <cstdlib>
#include <vector>

constexpr float PI = 3.14159265359f;
constexpr float DEG2RAD = (PI / 180);

namespace utils {
	float randRange(float a, float b);

	int randRangeInt(int a, int b);

	float interpolate(float t, float a, float b);

	template <typename T>
	T clamp(const T& n, const T& lower, const T& upper) {
		return std::max(lower, std::min(n, upper));
	}

	template <typename T>
	int sign(T val) {
		return (T(0) < val) - (val < T(0));
	}
}