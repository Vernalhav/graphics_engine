#include "AmbientLight.h"
#include "Scene.h"

AmbientLight::AmbientLight(SceneObject* obj, const glm::vec3& diffuse, float intensity)
	: Light(obj, diffuse, intensity) {
	Scene::getActiveScene()->setAmbientLight(this);
}
