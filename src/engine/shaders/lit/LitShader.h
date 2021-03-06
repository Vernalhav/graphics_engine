#pragma once
#include "../../../graphics/Shader.h"
#include "../../AmbientLight.h"
#include "../../PointLight.h"
#include "../../SpotLight.h"
#include "../../../graphics/Material.h"


class LitShader : public Shader {
private:
	static constexpr int POSITION_LAYOUT_LOC = 0;
	static constexpr int TEX_COORD_LAYOUT_LOC = 1;
	static constexpr int NORMAL_LAYOUT_LOC = 2;

	static constexpr int MODEL_MATRIX_UNIFORM_LOC = 0;
	static constexpr int VIEW_PROJ_MATRIX_UNIFORM_LOC = 1;
	static constexpr int MAIN_TEX_UNIFORM_LOC = 3;

	static constexpr int VIEW_POS_UNIFORM_LOC = 2;
	static constexpr int LIGHTING_ENABLED_UNIFORM_LOC = 4;
	static constexpr int LIGHT_BLOCK_BINDING = 0;
	static constexpr int MAX_LIGHTS = 128;		// Should be the same as the one defined in the frag shader
	static constexpr int LIGHT_BUFFER_LEN = 48 + MAX_LIGHTS * 48 + MAX_LIGHTS * 64;

	static int lightsUboId;

	static void generateLightBuffers();

	static int writeAmbientLightToBuffer(void* buffer, AmbientLight* light, int offset);
	static int writePointLightToBuffer(void* buffer, PointLight* light, int offset);
	static int writeSpotLightToBuffer(void* buffer, SpotLight* light, int offset);

public:
	LitShader(const std::string& name);

	void setMaterial(const Material& material) override;
	void setLightingEnabled(bool enabled);

	static void updateLights(AmbientLight* ambient,
		const std::vector<PointLight*>& pointLights,
		const std::vector<SpotLight*>& spotLights);
	
	static void freeLightBuffers();

	virtual void setAttributeLayout() override;
	virtual void enableAttributes() override;

	// Inherited via Shader
	virtual void setViewPosition(const glm::vec3& position) override;

	virtual int getModelMatrixUniformLoc() override;
	virtual int getViewProjectionUniformLoc() override;
	virtual int getMainTextureUniformLoc() override;
};