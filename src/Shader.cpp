#include "Shader.h"
#include <iostream>


Shader::Shader(const std::string& vertexCode, const std::string& fragmentCode) : Shader(vertexCode, fragmentCode, "Unnamed Shader") {
}

Shader::Shader(const std::string& vertexCode, const std::string& fragmentCode, const std::string& name) : name(name) {
	this->id = glCreateProgram();

	GLuint vertex = Shader::compileShader(vertexCode, GL_VERTEX_SHADER, this->name + ": Vertex shader");
	GLuint fragment = Shader::compileShader(fragmentCode, GL_FRAGMENT_SHADER, this->name + ": Fragment shader");

    glAttachShader(this->id, vertex);
    glAttachShader(this->id, fragment);

    glLinkProgram(this->id);
    this->use();
}

void Shader::use() {
    glUseProgram(this->id);
}

void Shader::setTransform(const Transform& t) {
    setFloat2("translation", t.translation);
    setFloat("scale", t.scale);
    setFloat("rotation", t.rotation);
}

GLint Shader::getUniformLocation(const std::string& name) {
    return glGetUniformLocation(id, name.c_str());
}

void Shader::setFloat(const std::string& name, float value) {
    auto location = getUniformLocation(name);
    return glUniform1f(location, value);
}

void Shader::setFloat2(const std::string& name, Vector2 values) {
    auto location = getUniformLocation(name);
    return glUniform2f(location, values.x, values.y);
}

void Shader::setFloat4(const std::string& name, Vector4 values) {
    auto location = getUniformLocation(name);
    return glUniform4f(location, values.x, values.y, values.z, values.w);
}

/// <summary>
/// Compiles shader of a certain type from string code
/// and returns its ID. Name is used to improve error
/// logging.
/// </summary>
/// <param name="code">String with the shader code</param>
/// <param name="type">Either GL_VERTEX_SHADER or GL_FRAGMENT_SHADER</param>
/// <param name="name">String to identify this shader in case of compilation errors</param>
/// <returns>Shader ID</returns>
GLuint Shader::compileShader(const std::string& code, GLuint type, const std::string& name) {
	auto shader = glCreateShader(type);
	const char* codeStr = code.c_str();
	glShaderSource(shader, 1, &codeStr, NULL);
	glCompileShader(shader);

    GLint isCompiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE) {

        int infoLength = 512;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLength);

        char* info = (char*)malloc(infoLength * sizeof(char));
        glGetShaderInfoLog(shader, infoLength, NULL, info);

        std::cout << "Error compiling shader [" << name << "]. Info: " << info << std::endl;

        free(info);
    }

    return shader;
}