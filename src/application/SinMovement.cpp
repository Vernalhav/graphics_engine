#include "SinMovement.h"

SinMovement::SinMovement(SceneObject* obj, float amplitude, float frequency, const glm::vec3& direction)
	: Component(obj), direction(direction), amplitude(amplitude), frequency(frequency), time(0){ }

void SinMovement::update() {
	time += (float)Component::deltaTime;
	sceneObject->transform.translate(direction * amplitude * std::sin(frequency * time));
}
