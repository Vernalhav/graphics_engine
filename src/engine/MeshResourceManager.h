#pragma once
#include <unordered_map>
#include <string>
#include "../graphics/MeshLoader.h"

using MeshResourceId = std::string;

namespace MeshResourceManager {	
	
	/// <summary>
	/// Loads a new resource if it isn't loaded already,
	/// or returns if it is.
	/// </summary>
	static void addResource(const MeshResourceId& id, const std::string& texturePath);

	/// <summary>
	/// Returns a pointer to a resource's data, or returns
	/// nullptr if it is not found.
	/// NOTE: This function should ideally load the resource
	/// if it is not found, but currently we need more parameters
	/// to construct MeshRenderData than just its resourceID, so
	/// the method addResource was created to handle this issue.
	/// </summary>
	static MeshRenderData* getResource(const MeshResourceId& resource);

	/// <summary>
	/// Unloads resource and frees its memory if it exists.
	/// Otherwise, issues a warning.
	/// </summary>
	static void unloadResource(const MeshResourceId& resource);
	
	/// <summary>
	/// Frees and unloads all resources.
	/// </summary>
	static void unloadResources();
};