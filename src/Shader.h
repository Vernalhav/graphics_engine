#pragma once
#include <string>
#include <gl/glew.h>

#include "vectors.h"
#include "Transform.h"

class Shader
{
private:
	std::string name;
	GLuint id;

	static GLuint compileShader(const std::string& code, GLuint type, const std::string& name);
	GLint getUniformLocation(const std::string& name);

public:
	Shader() : name("Unnamed Shader"), id(-1) { }
	Shader(const std::string& vertexCode, const std::string& fragmentCode);
	Shader(const std::string& vertexCode, const std::string& fragmentCode, const std::string& name);
	~Shader() { }

	void use();
	void setTransform(const Transform& t);

	void setFloat(const std::string& name, float value);
	void setFloat2(const std::string& name, Vector2 values);
	void setFloat4(const std::string& name, Vector4 values);
};

