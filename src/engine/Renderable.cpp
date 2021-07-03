#include "Renderable.h"
#include "Scene.h"

Renderable::Renderable(SceneObject* parent, RenderData* data)
	: Component(parent), renderData(data) {
	Scene::activeScene->renderer->uploadMesh(data);
}

Renderable::~Renderable() { delete renderData; }

RenderData* Renderable::getRenderData() {
	return renderData;
}
