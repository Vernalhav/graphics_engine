#include "MeshResourceManager.h"
#include "../graphics/MeshLoader.h"

#include <iostream>


// Creating an anonymous namespace to restrict access to this file.
// (Essentially creating "private" variables and functions)
namespace {
    /// <summary>
    /// Mapping between resource paths on the filesystem and
    /// their corresponding resource.
    /// Using paths as unique identifiers is not ideal and
    /// should be changed to a more stable alternative in the future.
    /// </summary>
    static std::unordered_map<MeshResourceId, MeshRenderData*> resources;
}

static void MeshResourceManager::addResource(const MeshResourceId& id, const std::string& texturePath) {
    if (resources.count(id))
        return;

    resources[id] = MeshLoader::loadMesh(id, texturePath);
}

MeshRenderData* MeshResourceManager::getResource(const MeshResourceId& resource) {
    if (resources.count(resource)) {
        return resources[resource];
    }
    
    std::cout << "getResource: WARNING: could not locate resource " << resource << std::endl;
    return nullptr;
}

void MeshResourceManager::unloadResource(const MeshResourceId& resource) {
    if (!resources.count(resource)) {
        std::cout << "unloadResource: WARNING: could not find resource " << resource << std::endl;
        return;
    }

    delete resources[resource];
    resources.erase(resource);
    return;
}

void MeshResourceManager::unloadResources() {
    for (auto& elementPair : resources) {
        delete elementPair.second;
    }
    resources.clear();
}
