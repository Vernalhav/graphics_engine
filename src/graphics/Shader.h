#pragma once
#include <string>
#include <gl/glew.h>

#include <glm/glm.hpp>
#include "../engine/Transform.h"

class Shader
{
private:
	std::string name;
	GLuint id;

	static GLuint compileShader(const std::string& code, GLuint type, const std::string& name);
	GLint getUniformLocation(const std::string& name);
	GLint getAttribLocation(const std::string& name);

public:
	Shader() : name("Unnamed Shader"), id(0) { }
	Shader(const std::string& vertexCode, const std::string& fragmentCode);
	Shader(const std::string& vertexCode, const std::string& fragmentCode, const std::string& name);
	~Shader() { }

	void use();

	// Sets the model matrix in the shader to the specified values.
	void setTransform(const Transform& t);
	void setTransform(const glm::mat3& t);

	void setPositionAttributeLayout();	// Configures the VAO's input attribute layout
	void enableAttrib(const std::string& name);

	void setFloat(const std::string& name, float value);
	void setFloat2(const std::string& name, glm::vec2 values);
	void setFloat3(const std::string& name, glm::vec3 values);
	void setFloat4(const std::string& name, glm::vec4 values);
	void setMatrix4(const std::string& name, glm::mat4 values);
};

