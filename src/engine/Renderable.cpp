#include "Renderable.h"

Renderable::Renderable(SceneObject* parent, RenderData* data)
	: Component(parent), renderData(data) { }