#include "Shader.h"

#include <glm/gtc/type_ptr.hpp>
#include <iostream>


Shader::Shader(const std::string& vertexCode, const std::string& fragmentCode)
    : Shader(vertexCode, fragmentCode, "Unnamed Shader") { }

Shader::Shader(const std::string& vertexCode, const std::string& fragmentCode, const std::string& name)
    : name(name) {
	id = glCreateProgram();

	GLuint vertex = Shader::compileShader(vertexCode, GL_VERTEX_SHADER, name + ": Vertex shader");
	GLuint fragment = Shader::compileShader(fragmentCode, GL_FRAGMENT_SHADER, name + ": Fragment shader");

    glAttachShader(id, vertex);
    glAttachShader(id, fragment);

    // TODO: Add error checking here
    glLinkProgram(id);
    use();

    // Sets the main texture sampler to read the texture
    // that is assigned to the main texture slot.
    setInt(MAIN_TEXTURE_LAYOUT_LOC, MAIN_TEXTURE_SLOT);
}

Shader::~Shader() {
    glDeleteProgram(id);
}

void Shader::use() {
    glUseProgram(id);
}

void Shader::setMVPMatrix(const glm::mat4 & mvp) {
    setMatrix4(MVP_MATRIX_LAYOUT_LOC, mvp);
}

void Shader::setAttributeLayout() {
    glVertexAttribPointer(POSITION_LAYOUT_LOC, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (const void*)0);
    glVertexAttribPointer(TEX_COORD_LAYOUT_LOC, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (const void*)(3*sizeof(float)));
}

void Shader::enableAttributes() {
    enableAttrib(POSITION_LAYOUT_LOC);
    enableAttrib(TEX_COORD_LAYOUT_LOC);
}

void Shader::enableAttrib(const std::string& name) {
    auto location = getAttribLocation(name);
    enableAttrib(location);
}

void Shader::enableAttrib(int location) {
    glEnableVertexAttribArray(location);
}

void Shader::setInt(const std::string& name, int value) {
    auto location = getUniformLocation(name);
    setInt(location, value);
}

void Shader::setInt(int location, int value) {
    glUniform1i(location, value);
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
    setFloat(location, value);
}

void Shader::setFloat(int location, float value) {
    glUniform1f(location, value);
}

void Shader::setFloat2(const std::string& name, const glm::vec2& values) {
    auto location = getUniformLocation(name);
    setFloat2(location, values);
}

void Shader::setFloat2(int location, const glm::vec2& values) {
    glUniform2f(location, values.x, values.y);
}

void Shader::setFloat3(const std::string& name, const glm::vec3& values) {
    auto location = getUniformLocation(name);
    setFloat3(location, values);
}

void Shader::setFloat3(int location, const glm::vec3& values) {
    glUniform3f(location, values.x, values.y, values.z);
}

void Shader::setFloat4(const std::string& name, const glm::vec4& values) {
    auto location = getUniformLocation(name);
    setFloat4(location, values);
}

void Shader::setFloat4(int location, const glm::vec4& values) {
    glUniform4f(location, values.x, values.y, values.z, values.w);
}

void Shader::setMatrix4(const std::string& name, const glm::mat4& values) {
    auto location = getUniformLocation(name);
    setMatrix4(location, values);
}

void Shader::setMatrix4(int location, const glm::mat4& values) {
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