#pragma once

#include <gl/glew.h>
#include <glm/glm.hpp>
#include <vector>

#include "Shader.h"
#include "RenderData.h"

enum class PolygonMode;

class Renderer {
private:
	PolygonMode polygonMode;
	GLuint VAO;
	Shader* shader;

public:
	Renderer(Shader* s);
	~Renderer();

	void uploadMesh(RenderData* mesh);

	void setViewPosition(const glm::vec3& position);

	void drawObject(RenderData* object, const glm::mat4& model, const glm::mat4& viewProjection);

	void toggleDrawMode();
};