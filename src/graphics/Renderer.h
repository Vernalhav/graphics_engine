#pragma once

#include <vector>
#include <gl/glew.h>

#include "../engine/SceneObject.h"
#include "../math/matrix.h"
#include "Primitive.h"
#include "Shader.h"


class Renderer {
private:
	GLuint VAO, VBO;
	Shader shader;

	/// <summary>
	/// Internal recursive function that draws all of object's
	/// primitives according to the relative transformation of
	/// all of its parents.
	/// </summary>
	/// <param name="object">Root object to be drawn</param>
	/// <param name="globalTransform">Accumulated transform matrix of all of object's parents</param>
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