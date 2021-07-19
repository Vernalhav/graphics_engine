#include "LitShader.h"

// TODO: improve buffer handling (probably by creating a GameRenderer class that stores this state)
int LitShader::pointLightUboId = -1;

void LitShader::generateLightBuffers() {
    glGenBuffers(1, (GLuint *)&pointLightUboId);
    glBindBuffer(GL_UNIFORM_BUFFER, pointLightUboId);
    glBufferData(GL_UNIFORM_BUFFER, POINT_LIGHT_BUFFER_LEN, nullptr, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, LIGHT_BLOCK_BINDING, pointLightUboId);
}

LitShader::LitShader(const std::string& name)
    : Shader(fs::path("."), name) {
    
    if (pointLightUboId == -1) {
        LitShader::generateLightBuffers();
    }
}

void LitShader::updateLights(AmbientLight* ambient, std::vector<PointLight*> pointLights) {
    // TODO
}

void LitShader::freeLightBuffers() {
    glDeleteBuffers(1, (GLuint *)&pointLightUboId);
    pointLightUboId = -1;
}

void LitShader::setAttributeLayout() {
    glVertexAttribPointer(POSITION_LAYOUT_LOC, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (const void*)0);
    glVertexAttribPointer(TEX_COORD_LAYOUT_LOC, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (const void*)(3 * sizeof(float)));
    glVertexAttribPointer(NORMAL_LAYOUT_LOC, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (const void*)(5 * sizeof(float)));
}

void LitShader::enableAttributes() {
    enableAttrib(POSITION_LAYOUT_LOC);
    enableAttrib(TEX_COORD_LAYOUT_LOC);
    enableAttrib(NORMAL_LAYOUT_LOC);
}

int LitShader::getModelMatrixUniformLoc() {
    return MODEL_MATRIX_UNIFORM_LOC;
}

int LitShader::getViewProjectionUniformLoc() {
    return VIEW_PROJ_MATRIX_UNIFORM_LOC;
}

int LitShader::getMainTextureUniformLoc() {
    return MAIN_TEX_UNIFORM_LOC;
}
