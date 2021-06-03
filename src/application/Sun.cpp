#include "Sun.h"
#include "../misc/utils.h"


Sun::Sun(SceneObject* obj, const Vector3& colorStart, const Vector3& colorEnd)
	: Component(obj), colorStart(colorStart), colorEnd(colorEnd), frameNumber(0), initialScale(0) { }

void Sun::update() {
	float deltaPerFrame = 0.0005f;
	float t = 0.5f * sin(2 * PI * frameNumber * deltaPerFrame) + 0.5f;
	
	Vector3 result = Vector3::interpolate(t, colorStart, colorEnd);
	sceneObject->transform.scale = utils::interpolate(t, 2/3.0f * initialScale, 4/3.0f * initialScale );
	sceneObject->setPrimitiveColor(result, 1);

	frameNumber++;
}

void Sun::start() {
	initialScale = sceneObject->transform.scale;
}
