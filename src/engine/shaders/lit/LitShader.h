#pragma once
#include "../../../graphics/Shader.h"

class LitShader : public Shader {
public:
	LitShader(const std::string& name);

	// Inherited via Shader
	virtual void setAttributeLayout() override;
	virtual void enableAttributes() override;
};