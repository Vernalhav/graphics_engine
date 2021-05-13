#pragma once

#include <vector>
#include <gl/glew.h>

#include "Primitive.h"
#include "SceneObject.h"


class Renderer {
	/// <summary>
	/// Uploads the scene objects' vertex data to a Vertex Buffer Object
	/// and writes to each Primitive's offset member and returns the name
	/// of the created VBO.
	/// </summary>
	/// <param name="objects">Top-level objects in the scene</param>
	GLuint uploadObjects(std::vector<SceneObject*> objects);
};