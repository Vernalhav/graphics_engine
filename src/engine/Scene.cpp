#include "Scene.h"
#include "Renderable.h"

#include "shaders/lit/LitShader.h"

#include <string.h>
#include <iostream>
#include <stack>

Scene* Scene::activeScene = nullptr;


Scene::Scene() : mainCamera(nullptr), ambientLight(nullptr) {
	if (activeScene == nullptr) activeScene = this;
	root = new SceneObject("root");
	renderer = new Renderer(new LitShader("Standard Shader"));
}

Scene::~Scene() {
	mainCamera = nullptr;
	ambientLight = nullptr;
	LitShader::freeLightBuffers();

	delete root;
	delete renderer;
}

void Scene::addRootObject(SceneObject* object) {
	root->appendChild(object);
}

void Scene::setMainCamera(Camera* camera) {
	mainCamera = camera;
}

void Scene::makeActiveScene() {
	activeScene = this;
}

void Scene::addPointLight(PointLight* light) {
	pointLights.push_back(light);
}

void Scene::setAmbientLight(AmbientLight* light) {
	ambientLight = light;
}

void Scene::render() {
	if (mainCamera == nullptr) {
		std::cout << "render: WARNING: No main camera assigned!" << std::endl;
		return;
	}

	glm::mat4 viewProjectionMatrix = mainCamera->getViewProjectionMatrix();

	glm::vec3 viewPosition = mainCamera->getViewPosition();
	renderer->setViewPosition(viewPosition);
	LitShader::updateLights(ambientLight, pointLights);
	
	std::stack<std::pair<const SceneObject*, glm::mat4>> objects;
	objects.push({ root, root->transform.getTransformMatrix() });

	while (!objects.empty()) {
		const auto& top = objects.top();

		const SceneObject* curObj = top.first;
		glm::mat4 globalTransform = top.second * curObj->transform.getTransformMatrix();

		objects.pop();

		std::vector<Renderable*> renderables = curObj->getComponents<Renderable>();
		for (Renderable* renderable : renderables) {
			renderer->drawObject(renderable->getRenderData(), globalTransform, viewProjectionMatrix);
		}

		// Simulate recursion by propagating current global transform
		for (const SceneObject* child : curObj->getChildren()) {
			objects.push({ child, globalTransform });
		}
	}
}

void Scene::start() {
	root->start();
}

void Scene::update() {
	root->update();
}

void Scene::toggleDrawMode() {
	renderer->toggleDrawMode();
}

void Scene::setLightingEnabled(bool value) {
	LitShader* shader = dynamic_cast<LitShader*>(renderer->getShader());
	if (shader != nullptr) {
		shader->setLightingEnabled(value);
	}
}

Scene* Scene::getActiveScene() {
	return activeScene;
}
