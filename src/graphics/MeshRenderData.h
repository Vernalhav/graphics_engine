#pragma once

#include <string>
#include <vector>
#include "Vertex.h"
#include "Texture.h"


struct MeshRenderData {
	std::vector<Vertex> vertices;	// Unique vertices and their attributes
	std::vector<int> indices;		// Vertex indices for each face (GL_TRIANGLES)
	
	Texture texture;
	std::string materialPath;

	MeshRenderData();
	MeshRenderData(const std::string& texturePath);

	friend class Renderer;

private:
	int vaoId;	// Id of the Mesh's OpenGL vertex array object
	int vboId;	// Id of the Mesh's OpenGL vertex buffer object
	int eboId;	// Id of the Mesh's OpenGL index buffer object
};