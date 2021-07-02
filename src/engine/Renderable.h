#pragma once
#include "SceneObject.h"
#include "../graphics/RenderData.h"

class Renderable : public Component {
private:
	friend class Renderer;
	RenderData* renderData;

public:
	Renderable(SceneObject* parent, RenderData* data);
};