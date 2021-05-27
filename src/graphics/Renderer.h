#pragma once

#include <vector>
#include <gl/glew.h>

#include "../math/matrix.h"
#include "Primitive.h"
#include "Shader.h"
#include "SceneObject.h"


class Renderer {
private:
	GLuint VAO, VBO;
	Shader shader;

	void _drawObject(const SceneObject* object, Matrix3 globalTransform);

public:
	Renderer(Shader s);

	/// <summary>
	/// Uploads the scene objects' vertex data to a Vertex Buffer Object
	/// and writes to each Primitive's offset member.
	/// </summary>
	/// <param name="objects">Top-level objects in the scene</param>
	void uploadObjects(std::vector<SceneObject*> objects);

	void drawObject(SceneObject* object);
};