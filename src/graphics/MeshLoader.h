#pragma once

#include <vector>
#include <string>

#include "MeshRenderData.h"


namespace MeshLoader {
	/// <summary>
	/// Loads .obj file into a mesh object.
	/// texturePath is an optional image file
	/// (This function does not yet 
	/// take materials into account)
	/// </summary>
	MeshRenderData* loadMesh(const std::string& filePath, const std::string& texturePath = "");
};