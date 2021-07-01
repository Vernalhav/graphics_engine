#include "Texture.h"


Texture::Texture(const std::string& texPath, GLenum wrapMode, GLenum rescaleFilter, int channelMode)
	: wrapMode(wrapMode), rescaleFilter(rescaleFilter), channelMode(channelMode) {
	
	int channels;
	image = (unsigned char *)stbi_load(texPath.c_str(), &width, &height, &channels, channelMode);

	glGenTextures(1, &textureId);
}

Texture::~Texture() {
	glDeleteTextures(1, &textureId);
	stbi_image_free(image);
}
