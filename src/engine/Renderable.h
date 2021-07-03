#pragma once
#include "SceneObject.h"
#include "../graphics/RenderData.h"

class Renderable : public Component {
private:
	RenderData* renderData;

public:
	Renderable(SceneObject* parent, RenderData* data);
	~Renderable();

	RenderData* getRenderData();
};