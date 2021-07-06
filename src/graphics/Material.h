#pragma once

#include <map>
#include <string>
#include <glm/glm.hpp>
#include <filesystem>
#include <glm/glm.hpp>

#include "Texture.h"

namespace fs = std::filesystem;

struct Material {

	std::string name;
	glm::vec3 color;
	Texture *texture;

	Material() : name(""), color(glm::vec3(0)), texture(nullptr) { };
	
	Material(const std::string& name, const glm::vec3& color, const fs::path& texturePath);

	void freeTexture() { delete texture; }
};