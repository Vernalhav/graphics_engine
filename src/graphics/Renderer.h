#pragma once

#include <gl/glew.h>
#include <glm/glm.hpp>
#include <vector>

#include "../engine/SceneObject.h"
#include "Shader.h"
#include "MeshLoader.h"


class Renderer {
private:
	GLuint VAO;
	Shader shader;

	/// <summary>
	/// Internal recursive function that draws all of object's
	/// primitives according to the relative transformation of
	/// all of its parents.
	/// </summary>
	/// <param name="object">Root object to be drawn</param>
	/// <param name="globalTransform">Accumulated transform matrix of all of object's parents</param>
	void _drawObject(const SceneObject* object, glm::mat4 globalTransform);

public:
	Renderer(Shader s);
	~Renderer();

	void uploadMesh(RenderData* mesh);

	void drawObject(RenderData* object, const glm::mat4& transform);
};