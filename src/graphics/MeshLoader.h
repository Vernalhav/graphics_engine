#pragma once

#include <vector>
#include <string>

#include "Vertex.h"


struct MeshRenderData {
	// We're not storing the mesh's VAO id because we'll assume we only have one shader
	std::string texturePath;
	std::string materialPath;
	std::vector<Vertex> vertices;	// Unique vertices and their attributes
	std::vector<int> indices;		// Vertex indices for each face (GL_TRIANGLES)
};


namespace MeshLoader {
	/// <summary>
	/// Loads .obj file into a mesh object.
	/// texturePath is an optional image file
	/// (This function does not yet 
	/// take materials into account)
	/// </summary>
	MeshRenderData* loadMesh(const std::string& filePath, const std::string& texturePath = "");
};