#pragma once
#include <string>
#include <gl/glew.h>

#include <glm/glm.hpp>
#include <filesystem>


namespace fs = std::filesystem;

class Shader
{
private:
	std::string name;
	GLuint id;

	static GLuint compileShader(const std::string& code, GLuint type, const std::string& name);
	void initShader(const std::string& vertexCode, const std::string& fragmentCode);
	GLint getUniformLocation(const std::string& name);
	GLint getAttribLocation(const std::string& name);

public:
	static constexpr int POSITION_LAYOUT_LOC = 0;
	static constexpr int TEX_COORD_LAYOUT_LOC = 1;
	static constexpr int MVP_MATRIX_LAYOUT_LOC = 0;
	static constexpr int MAIN_TEXTURE_LAYOUT_LOC = 1;
	static constexpr int MAIN_TEXTURE_SLOT = 0;

	Shader(const fs::path& directoryPath, const std::string& name = "Unnamed shader");
	Shader(const std::string& vertexCode, const std::string& fragmentCode, const std::string& name = "Unnamed shader");
	~Shader();

	void use();

	// Hardcoded: Sets the MVP matrix in the shader to the specified values.
	void setMVPMatrix(const glm::mat4 & mvp);

	virtual void setAttributeLayout() = 0;	// Hardcoded: Configures the VAO's input attribute layout
	virtual void enableAttributes() = 0;	// Hardcoded
	void enableAttrib(const std::string& name);
	void enableAttrib(int location);

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

