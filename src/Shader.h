#pragma once
#include <string>
#include <gl/glew.h>

class Shader
{
private:
	std::string name;
	int id;

	static GLuint compileShader(std::string code, GLuint type, std::string name = "");

public:
	Shader() : name("Unnamed Shader"), id(-1) { }
	Shader(std::string vertexCode, std::string fragmentCode);
	Shader(std::string vertexCode, std::string fragmentCode, std::string name);
	~Shader() { }

	void use();
};

