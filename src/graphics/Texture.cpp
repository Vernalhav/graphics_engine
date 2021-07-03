#include "Texture.h"

#include <iostream>

#include "Shader.h"

Texture::Texture()
	: image(nullptr), wrapMode(GL_REPEAT), rescaleFilter(GL_LINEAR),
	  width(0), height(0), channelMode(STBI_rgb), textureId(0) { }

Texture::Texture(const std::string& texPath, GLenum wrapMode, GLenum rescaleFilter, int channelMode)
	: wrapMode(wrapMode), rescaleFilter(rescaleFilter), channelMode(channelMode), textureId(0) {
	
	stbi_set_flip_vertically_on_load(1);

	int channels;
	image = (unsigned char *)stbi_load(texPath.c_str(), &width, &height, &channels, channelMode);
	if (image == nullptr) {
		std::cout << "Texture: WARNING: Could not load image " << texPath << std::endl;
		return;
	}

	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, rescaleFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, rescaleFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);

	GLenum imageChannelMode = -1;
	if (channelMode == STBI_rgb) imageChannelMode = GL_RGB;
	else if (channelMode == STBI_rgb_alpha) imageChannelMode = GL_RGBA;
	else {
		std::cout << "Texture: WARNING: Invalid channel mode " << channelMode << std::endl;
	}
	
	const int LOD = 0;
	glTexImage2D(GL_TEXTURE_2D, LOD, imageChannelMode, width, height, 0, imageChannelMode, GL_UNSIGNED_BYTE, image);
}

Texture::~Texture() {
	glDeleteTextures(1, &textureId);
	stbi_image_free(image);
}

void Texture::bind(int textureSlot) {
	if (textureSlot < 0 || textureSlot >= GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS) {
		std::cout << "Texture: WARNING: Could not bind textureSlot " << textureSlot << std::endl;
		return;
	}
	glActiveTexture(GL_TEXTURE0 + textureSlot);
	glBindTexture(GL_TEXTURE_2D, textureId);
}

void Texture::unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}