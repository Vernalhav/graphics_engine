#include "Material.h"


Material::Material(const std::string& name,
	const fs::path& texturePath,
	const glm::vec3& ambient,
	const glm::vec3& diffuse,
	const glm::vec3& specular,
	float shinyness,
	IlluminationMode illumMode)
	: name(name),
	  ambient(ambient),
	  diffuse(diffuse),
	  specular(specular),
	  shinyness(shinyness),
	  illumMode(illumMode),
	  texture(nullptr) {
	
	if (texturePath.empty()) return;
	texture = new Texture(texturePath);
}
