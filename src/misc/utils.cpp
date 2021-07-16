#include "utils.h"

#include <cstdlib>
#include <iostream>
#include <fstream>


float utils::randRange(float a, float b) {
    return (rand() / (float)RAND_MAX) * (b - a) + a;
}

int utils::randRangeInt(int a, int b) {
    return rand() % (b - a + 1) + a;
}

float utils::interpolate(float t, float a, float b) {
    return (1 - t) * a + t * b;
}

glm::vec3 utils::projectToPlane(const glm::vec3& v, const glm::vec3& planeNormal) {
    float normalLen = glm::length(planeNormal);
    return glm::normalize(v - planeNormal * glm::dot(v, planeNormal)/(normalLen * normalLen));
}

std::string utils::readFileAsString(const fs::path& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cout << "readFileAsString: WARNING: could not open file " << path << std::endl;
        return "";
    }

    return std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
}

std::vector<std::string> utils::split(const std::string& s, char delimiter, bool skipConsecutives) {
    std::vector<std::string> splits;

    size_t i = 0, j = -1;
    for (i = 0, j = -1; (j = s.find(delimiter, j + 1)) != std::string::npos; i = j + 1) {
        if (skipConsecutives && j <= i) continue;

        splits.push_back(s.substr(i, j - i));
    }
    if (skipConsecutives && i >= s.size()) return splits;

    splits.push_back(s.substr(i, std::string::npos));
    return splits;
}
