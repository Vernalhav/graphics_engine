#pragma once

#include <map>
#include <string>
#include <glm/glm.hpp>
#include <filesystem>
#include <glm/glm.hpp>

#include "Texture.h"

namespace fs = std::filesystem;

enum class IlluminationMode {
	Flat = 0,
	Diffuse = 1,
	Specular = 2
};

struct Material {

	std::string name;
	Texture *texture;

	IlluminationMode illumMode;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shinyness;
	
	Material(const std::string& name = "",
			const fs::path& texturePath = "",
			const glm::vec3& ambient = glm::vec3(1),
			const glm::vec3& diffuse = glm::vec3(1),
			const glm::vec3& specular = glm::vec3(0),
			float shinyness = 0.0f,
			IlluminationMode illumMode = IlluminationMode::Diffuse);

	void freeTexture() { delete texture; }
};