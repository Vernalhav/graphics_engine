#include "Material.h"

Material::Material(const std::string& name, const glm::vec3& color, const fs::path& texturePath)
	: name(name), color(color) {
	
	texture = new Texture(texturePath);
}
