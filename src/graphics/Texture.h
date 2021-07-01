#pragma once

#include <gl/glew.h>
#include <string>

#include "../external/stb_image.h"


struct Texture {
	
	unsigned char* image;
	GLenum rescaleFilter;
	GLenum wrapMode;
	GLuint textureId;

	int channelMode;
	int width;
	int height;

	Texture();
	Texture(const std::string& texPath, GLenum wrapMode = GL_REPEAT,
		GLenum rescaleFilter = GL_LINEAR, int channelMode = STBI_rgb);
	
	~Texture();

	void bind(int textureSlot);
};

