#include "Sun.h"
#include "../misc/utils.h"


Sun::Sun(SceneObject* obj, const glm::vec3& colorStart, const glm::vec3& colorEnd)
	: Component(obj), colorStart(colorStart), colorEnd(colorEnd), frameNumber(0), initialScale(0) { }

void Sun::update() {

}

void Sun::start() {
	initialScale = sceneObject->transform.scale.x;
}
