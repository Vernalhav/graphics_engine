#pragma once

#include <vector>
#include <string>

#include "Vertex.h"


struct Mesh {
	std::string material;
	std::vector<Vertex> vertices;
	std::vector<int> indices;
};


namespace MeshLoader {
	/// <summary>
	/// Loads .obj file into a mesh object
	/// </summary>
	Mesh* loadMesh(const std::string& filePath);
};