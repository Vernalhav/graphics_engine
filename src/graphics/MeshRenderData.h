#pragma once

#include <string>
#include <vector>
#include "Vertex.h"


struct MeshRenderData {
	std::string texturePath;
	std::string materialPath;
	std::vector<Vertex> vertices;	// Unique vertices and their attributes
	std::vector<int> indices;		// Vertex indices for each face (GL_TRIANGLES)

	MeshRenderData() : vaoId(-1), vboId(-1), eboId(-1), texturePath(""), materialPath("") { }

	friend class Renderer;

private:
	int vaoId;	// Id of the Mesh's OpenGL vertex array object
	int vboId;	// Id of the Mesh's OpenGL vertex buffer object
	int eboId;	// Id of the Mesh's OpenGL index buffer object
};