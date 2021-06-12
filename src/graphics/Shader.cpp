#include "Shader.h"

#include <glm/gtc/type_ptr.hpp>
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
    setTransform(t.getTransformMatrix());
}

void Shader::setTransform(const glm::mat4& t) {
    setMatrix4("model", t);
}

void Shader::setPositionAttributeLayout() {
    auto location = getAttribLocation("position");
    glVertexAttribPointer((GLuint)location, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (const void*)0);
}

void Shader::enableAttrib(const std::string& name) {
    auto location = getAttribLocation(name);
    glEnableVertexAttribArray(location);
}

GLint Shader::getUniformLocation(const std::string& name) {
    GLint status =  glGetUniformLocation(id, name.c_str());
    if (status == -1)
        std::cout << "ERROR FINDING UNIFORM " << name << std::endl;
    return status;
}

GLint Shader::getAttribLocation(const std::string& name) {
    GLint status = glGetAttribLocation(id, name.c_str());
    if (status == -1)
        std::cout << "ERROR FINDING ATTRIBUTE " << name << std::endl;
    return status;
}

void Shader::setFloat(const std::string& name, float value) {
    auto location = getUniformLocation(name);
    glUniform1f(location, value);
}

void Shader::setFloat2(const std::string& name, glm::vec2 values) {
    auto location = getUniformLocation(name);
    glUniform2f(location, values.x, values.y);
}

void Shader::setFloat3(const std::string& name, glm::vec3 values) {
    auto location = getUniformLocation(name);
    glUniform3f(location, values.x, values.y, values.z);
}

void Shader::setFloat4(const std::string& name, glm::vec4 values) {
    auto location = getUniformLocation(name);
    glUniform4f(location, values.x, values.y, values.z, values.w);
}

void Shader::setMatrix4(const std::string& name, glm::mat4 values) {
    auto location = getUniformLocation(name);
    glUniformMatrix4fv(location, 1, GL_FALSE, (const GLfloat*)glm::value_ptr(values));
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

    std::cout << "Compiling shader " << name << "... ";

    GLint isCompiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE) {

        int infoLength = 512;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLength);

        char* info = (char*)malloc(infoLength * sizeof(char));
        glGetShaderInfoLog(shader, infoLength, NULL, info);

        std::cout << "Error compiling shader [" << name << "]. Info: " << info << std::endl;

        free(info);
        return shader;
    }

    std::cout << "success!" << std::endl;
    return shader;
}