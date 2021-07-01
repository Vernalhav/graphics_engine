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
	static constexpr int POSITION_LAYOUT_LOC = 0;
	static constexpr int TEX_COORD_LAYOUT_LOC = 1;
	static constexpr int MODEL_LAYOUT_LOC = 0;
	static constexpr int MAIN_TEXTURE_LAYOUT_LOC = 1;
	static constexpr int MAIN_TEXTURE_SLOT = 0;

	Shader() : name("Unnamed Shader"), id(0) { }
	Shader(const std::string& vertexCode, const std::string& fragmentCode);
	Shader(const std::string& vertexCode, const std::string& fragmentCode, const std::string& name);
	~Shader() { }

	void use();

	// Sets the model matrix in the shader to the specified values.
	void setTransform(const Transform& t);
	void setTransform(const glm::mat4& t);

	void setAttributeLayout();	// Configures the VAO's input attribute layout
	void enableAttrib(const std::string& name);

	void setInt(const std::string& name, int value);
	void setInt(int location, int value);
	void setFloat(const std::string& name, float value);
	void setFloat(int location, float value);
	void setFloat2(const std::string& name, const glm::vec2& values);
	void setFloat2(int location, const glm::vec2& values);
	void setFloat3(const std::string& name, const glm::vec3& values);
	void setFloat3(int location, const glm::vec3& values);
	void setFloat4(const std::string& name, const glm::vec4& values);
	void setFloat4(int location, const glm::vec4& values);
	void setMatrix4(const std::string& name, const glm::mat4& values);
	void setMatrix4(int location, const glm::mat4& values);
};

