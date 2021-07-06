#pragma once

#include <vector>
#include <string>

#include "RenderData.h"
#include "Material.h"


namespace MeshLoader {
	/// <summary>
	/// Loads .obj file into a mesh object.
	/// texturePath is an optional image file
	/// (This function does not yet 
	/// take materials into account)
	/// </summary>
	RenderData* loadMesh(const std::string& filePath);
};