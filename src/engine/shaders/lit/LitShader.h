#pragma once
#include "../../../graphics/Shader.h"

class LitShader : public Shader {
private:
	static constexpr int POSITION_LAYOUT_LOC = 0;
	static constexpr int TEX_COORD_LAYOUT_LOC = 1;
	static constexpr int NORMAL_LAYOUT_LOC = 2;

	static constexpr int MODEL_MATRIX_UNIFORM_LOC = 0;
	static constexpr int VIEW_PROJ_MATRIX_UNIFORM_LOC = 1;
	static constexpr int MAIN_TEX_UNIFORM_LOC = 3;

	static constexpr int VIEW_POS_UNIFORM_LOC = 2;

public:
	LitShader(const std::string& name);

	// Inherited via Shader
	virtual void setAttributeLayout() override;
	virtual void enableAttributes() override;

	// Inherited via Shader
	virtual int getModelMatrixUniformLoc() override;
	virtual int getViewProjectionUniformLoc() override;
	virtual int getMainTextureUniformLoc() override;
};