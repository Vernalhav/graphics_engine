#include "LitShader.h"
#include <iostream>

// TODO: improve buffer handling (probably by creating a GameRenderer class that stores this state)
int LitShader::lightsUboId = -1;

void LitShader::generateLightBuffers() {
    glGenBuffers(1, (GLuint *)&lightsUboId);
    glBindBuffer(GL_UNIFORM_BUFFER, lightsUboId);
    glBufferData(GL_UNIFORM_BUFFER, LIGHT_BUFFER_LEN, nullptr, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, LIGHT_BLOCK_BINDING, lightsUboId);
}

int LitShader::writeAmbientLightToBuffer(void* buffer, AmbientLight* light, int offset) {
    glm::vec4 diffuse = glm::vec4(light->getDiffuseColor(), 1);
    float intensity = light->getIntensity();

    memcpy((char *)buffer + offset, &diffuse, sizeof(glm::vec4));
    offset += sizeof(glm::vec4);
    memcpy((char *)buffer + offset, &intensity, sizeof(float));
    offset += sizeof(float);

    return offset;
}

int LitShader::writePointLightToBuffer(void* buffer, PointLight* light, int offset) {
    glm::vec4 position = glm::vec4(light->getPosition(), 1);
    glm::vec4 diffuse = glm::vec4(light->getDiffuseColor(), 1);
    glm::vec4 coefficients = glm::vec4(light->getAttenuationCoefficients(), 1);
    
    memcpy((char*)buffer + offset, &position, sizeof(glm::vec4));
    offset += sizeof(glm::vec4);
    memcpy((char*)buffer + offset, &diffuse, sizeof(glm::vec4));
    offset += sizeof(glm::vec4);
    memcpy((char*)buffer + offset, &coefficients, sizeof(glm::vec4));
    offset += sizeof(glm::vec4);

    return offset;
}

int LitShader::writeSpotLightToBuffer(void* buffer, SpotLight* light, int offset) {
    glm::vec4 position = glm::vec4(light->getPosition(), 1);
    glm::vec4 direction = glm::vec4(light->getDirection(), 1);
    glm::vec4 diffuse = glm::vec4(light->getDiffuse(), 1);
    float innerAngleCos = glm::cos(light->getInnerAngle());
    float outerAngleCos = glm::cos(light->getOuterAngle());
    
    memcpy((char*)buffer + offset, &position, sizeof(glm::vec4));
    offset += sizeof(glm::vec4);
    memcpy((char*)buffer + offset, &direction, sizeof(glm::vec4));
    offset += sizeof(glm::vec4);
    memcpy((char*)buffer + offset, &diffuse, sizeof(glm::vec4));
    offset += sizeof(glm::vec4);
    memcpy((char*)buffer + offset, &innerAngleCos, sizeof(float));
    offset += sizeof(float);
    memcpy((char*)buffer + offset, &outerAngleCos, sizeof(float));
    offset += sizeof(float);

    return offset;
}

LitShader::LitShader(const std::string& name)
    : Shader(fs::path("src/engine/shaders/lit/"), name) {

    setMainTextureLocation(MAIN_TEX_UNIFORM_LOC);
    setLightingEnabled(true);

    if (lightsUboId == -1) {
        LitShader::generateLightBuffers();
    }
}

void LitShader::setMaterial(const Material& material) {
    setFloat4("material.ambient_3", glm::vec4(material.ambient, 1));
    setFloat4("material.diffuse_3", glm::vec4(material.diffuse, 1));
    setFloat4("material.specular_3", glm::vec4(material.specular, 1));
    setFloat("material.shinyness", material.shinyness);
    setInt("material.illumMode", (int)material.illumMode);
}

void LitShader::setLightingEnabled(bool enabled) {
    setInt(LIGHTING_ENABLED_UNIFORM_LOC, enabled ? 1 : 0);
}

void LitShader::updateLights(AmbientLight* ambient,
    const std::vector<PointLight*>& pointLights,
    const std::vector<SpotLight*>& spotLights) {
    
    if (pointLights.size() > MAX_LIGHTS || spotLights.size() > MAX_LIGHTS) {
        std::cout << "updateLights: WARNING: number of lights exceeded maximum of " << MAX_LIGHTS << std::endl;
    }

    static char lightBuffer[LIGHT_BUFFER_LEN];
    int nPointLights = std::min((int)pointLights.size(), MAX_LIGHTS);
    int nSpotLights = std::min((int)spotLights.size(), MAX_LIGHTS);
    int offset = 0;

    memcpy((char *)lightBuffer + offset, &nPointLights, sizeof(int));
    offset += sizeof(int);
    memcpy((char *)lightBuffer + offset, &nSpotLights, sizeof(int));
    offset += sizeof(int);

    offset = 16;
    writeAmbientLightToBuffer(lightBuffer, ambient, offset);

    offset = 48;
    for (int i = 0; i < nPointLights; i++) {
        writePointLightToBuffer(lightBuffer, pointLights[i], offset);
        offset += 48;
    }

    offset = 48 + MAX_LIGHTS * 48;
    for (int i = 0; i < nSpotLights; i++) {
        writeSpotLightToBuffer(lightBuffer, spotLights[i], offset);
        offset += 64;
    }

    glBindBuffer(GL_UNIFORM_BUFFER, lightsUboId);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, offset, (void *)lightBuffer);
}

void LitShader::freeLightBuffers() {
    glDeleteBuffers(1, (GLuint *)&lightsUboId);
    lightsUboId = -1;
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

void LitShader::setViewPosition(const glm::vec3& position) {
    setFloat3(VIEW_POS_UNIFORM_LOC, position);
}
