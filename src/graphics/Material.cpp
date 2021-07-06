#include "Material.h"

Material::Material(const std::string& name, const glm::vec3& color, const std::string& texturePath) 
	: name(name), color(color), texture(texturePath) {}