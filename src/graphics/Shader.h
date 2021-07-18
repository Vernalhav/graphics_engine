#pragma once
#include <string>
#include <gl/glew.h>

#include <glm/glm.hpp>
#include <filesystem>


namespace fs = std::filesystem;

class Shader
{
protected:
	std::string name;
	GLuint id;

	void initShader(const std::string& vertexCode, const std::string& fragmentCode);
	static GLuint compileShader(const std::string& code, GLuint type, const std::string& name);

	GLint getUniformLocation(const std::string& name);
	GLint getAttribLocation(const std::string& name);

public:
	static constexpr int MAIN_TEXTURE_SLOT = 0;

	Shader(const fs::path& directoryPath, const std::string& name = "Unnamed shader");
	Shader(const std::string& vertexCode, const std::string& fragmentCode, const std::string& name = "Unnamed shader");
	~Shader();

	void use();

	void setMVPMatrix(const glm::mat4& model, const glm::mat4& viewProjection);

	virtual void setAttributeLayout() = 0;
	virtual void enableAttributes() = 0;
	void enableAttrib(const std::string& name);
	void enableAttrib(int location);

	virtual int getModelMatrixUniformLoc() = 0;
	virtual int getViewProjectionUniformLoc() = 0;
	virtual int getMainTextureUniformLoc() = 0;

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

