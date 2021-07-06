#pragma once

#include <map>
#include <string>
#include <glm/glm.hpp>

#include "../misc/utils.h"
#include "Texture.h"

struct Material {

	std::string name;
	glm::vec3 color;
	Texture texture;

	Material(const std::string& name, const glm::vec3& color, const std::string& texturePath);

};
