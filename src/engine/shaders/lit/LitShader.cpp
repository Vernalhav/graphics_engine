#include "LitShader.h"

LitShader::LitShader(const std::string& name) : Shader(fs::path("."), name) {
}

void LitShader::setAttributeLayout() {
    glVertexAttribPointer(POSITION_LAYOUT_LOC, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (const void*)0);
    glVertexAttribPointer(TEX_COORD_LAYOUT_LOC, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (const void*)(3 * sizeof(float)));
    glVertexAttribPointer(NORMAL_LAYOUT_LOC, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (const void*)(5 * sizeof(float)));
}

void LitShader::enableAttributes() {
    enableAttrib(POSITION_LAYOUT_LOC);
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
