#include "MeshResourceManager.h"

#include <iostream>


// Creating an anonymous namespace to restrict access to this file.
// (Essentially creating "private" variables and functions)
namespace {

    struct ResourceData {
        RenderData* resource;
        int referenceCount;     // Number of users of this resource that have not unloaded yet

        ResourceData(RenderData* resource) : resource(resource), referenceCount(0) { }
        ResourceData() : resource(nullptr), referenceCount(0) { }
        ~ResourceData() {
            delete resource;
        }
    };

    /// <summary>
    /// Mapping between resource paths on the filesystem and
    /// their corresponding resource.
    /// Using paths as unique identifiers is not ideal and
    /// should be changed to a more stable alternative in the future.
    /// </summary>
    static std::unordered_map<MeshResourceId, ResourceData> resources;
}

void MeshResourceManager::addResource(const MeshResourceId& id) {
    if (!resources.count(id)) {
        resources[id] = new RenderData(id);
    }
    resources[id].referenceCount++;
}

RenderData* MeshResourceManager::getResource(const MeshResourceId& resource) {
    if (resources.count(resource)) {
        resources[resource].referenceCount++;
        return resources[resource].resource;
    }
    
    std::cout << "getResource: WARNING: could not locate resource " << resource << std::endl;
    return nullptr;
}

void MeshResourceManager::unloadResource(const MeshResourceId& resource) {
    if (!resources.count(resource)) {
        std::cout << "unloadResource: WARNING: could not find resource " << resource << std::endl;
        return;
    }

    resources[resource].referenceCount--;

    if (resources[resource].referenceCount <= 0) {
        delete resources[resource].resource;
        resources.erase(resource);
    }
}

void MeshResourceManager::unloadResources() {
    for (auto& elementPair : resources) {
        delete elementPair.second.resource;
    }
    resources.clear();
}
