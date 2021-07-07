#include "Confiner.h"
#include <algorithm>

Confiner::Confiner(SceneObject* obj, const glm::vec2& xBounds, const glm::vec2& yBounds, const glm::vec2& zBounds)
	: Component(obj), xBounds(xBounds), yBounds(yBounds), zBounds(zBounds) { }

void Confiner::update() {
	glm::vec3 translation = sceneObject->transform.getTranslation();

	translation.x = std::clamp( translation.x, xBounds[0], xBounds[1] );
	translation.y = std::clamp( translation.y, yBounds[0], yBounds[1] );
	translation.z = std::clamp( translation.z, zBounds[0], zBounds[1] );

	sceneObject->transform.setTranslation(translation);
}
