#pragma once

#include <gl/glew.h>
#include <string>
#include <filesystem>

#include "../external/stb_image.h"

namespace fs = std::filesystem;

struct Texture {
	
	unsigned char* image;
	GLenum rescaleFilter;
	GLenum wrapMode;
	GLuint textureId;

	int channelMode;
	int width;
	int height;

	Texture();
	Texture(const Texture& other);

	Texture(Texture&& other) noexcept;

	Texture(const fs::path& texPath, GLenum wrapMode = GL_REPEAT,
		GLenum rescaleFilter = GL_NEAREST, int channelMode = STBI_rgb);
	~Texture();
	
	Texture& operator=(Texture&& other) noexcept;

	void bind(int textureSlot);
	void unbind();
};

