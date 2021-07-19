#pragma once
#include "../../../graphics/Shader.h"
#include "../../PointLight.h"
#include "../../AmbientLight.h"

struct PointLightShaderData {
	glm::vec4 pos_3, color_3, attenuationCoefficients_3;
};

class LitShader : public Shader {
private:
	static constexpr int POSITION_LAYOUT_LOC = 0;
	static constexpr int TEX_COORD_LAYOUT_LOC = 1;
	static constexpr int NORMAL_LAYOUT_LOC = 2;

	static constexpr int MODEL_MATRIX_UNIFORM_LOC = 0;
	static constexpr int VIEW_PROJ_MATRIX_UNIFORM_LOC = 1;
	static constexpr int MAIN_TEX_UNIFORM_LOC = 3;

	static constexpr int VIEW_POS_UNIFORM_LOC = 2;
	static constexpr int LIGHT_BLOCK_BINDING = 0;
	static constexpr int MAX_POINT_LIGHTS = 32;	// Should be the same as the one defined in the frag shader
	static constexpr int POINT_LIGHT_BUFFER_LEN = 4 * sizeof(int) + MAX_POINT_LIGHTS * sizeof(PointLightShaderData);

	static int pointLightUboId;

	static void generateLightBuffers();

public:
	LitShader(const std::string& name);

	static void updateLights(AmbientLight* ambient, std::vector<PointLight*> pointLights);
	static void freeLightBuffers();

	// Inherited via Shader
	virtual void setAttributeLayout() override;
	virtual void enableAttributes() override;

	// Inherited via Shader
	virtual int getModelMatrixUniformLoc() override;
	virtual int getViewProjectionUniformLoc() override;
	virtual int getMainTextureUniformLoc() override;
};