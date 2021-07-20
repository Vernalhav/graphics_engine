#include "Material.h"


Material::Material(const fs::path& texturePath, const std::string& name, const glm::vec3& ambient,
	const glm::vec3& diffuse, const glm::vec3& specular, float shinyness, const glm::vec3& color)
	: name(name), ambient(ambient), diffuse(diffuse), specular(specular),
		shinyness(shinyness), color(color), texture(nullptr) {
	
	if (texturePath.empty()) return;
	texture = new Texture(texturePath);
}
