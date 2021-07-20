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

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shinyness;
	
	Material(const fs::path& texturePath = "", const std::string& name = "",
		const glm::vec3& ambient = glm::vec3(1),
		const glm::vec3& diffuse = glm::vec3(1),
		const glm::vec3& specular = glm::vec3(1),
		float shinyness = 1,
		const glm::vec3& color = glm::vec3(0));

	void freeTexture() { delete texture; }
};