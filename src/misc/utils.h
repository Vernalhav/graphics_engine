#pragma once

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <filesystem>

namespace fs = std::filesystem;

constexpr float PI = 3.14159265359f;
constexpr float DEG2RAD = (PI / 180);

namespace utils {
	float randRange(float a, float b);

	int randRangeInt(int a, int b);

	float interpolate(float t, float a, float b);

	glm::vec3 projectToPlane(const glm::vec3& v, const glm::vec3& planeNormal);

	std::string readFileAsString(const fs::path& path);

	/// <summary>
	/// Splits string s into an array of stirngs
	/// delimited by delimiter. Does not include
	/// delimiter in any of the strings of the
	/// array
	/// skipConsecutive determines whether or not
	/// to include empty strings in the returned
	/// array if there are consecutive delimiters.
	/// </summary>
	std::vector<std::string> split(const std::string& s, char delimiter = ' ', bool skipConsecutive = true);

	template <typename T>
	T clamp(const T& n, const T& lower, const T& upper) {
		return std::max(lower, std::min(n, upper));
	}

	template <typename T>
	int sign(T val) {
		return (T(0) < val) - (val < T(0));
	}
}