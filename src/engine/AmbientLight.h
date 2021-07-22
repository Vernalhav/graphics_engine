#pragma once
#include "Light.h"

class AmbientLight : public Light {
public:
	AmbientLight(SceneObject* obj, const glm::vec3& diffuse = glm::vec3(1), float intensity = 1);
};
