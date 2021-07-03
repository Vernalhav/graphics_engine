#include "Scene.h"

#include <string.h>
#include <iostream>
#include <stack>
#include "Renderable.h"

Scene* Scene::activeScene = nullptr;

const std::string vertex_code =
	"#version 430 core\n"
	"layout(location = 0) in vec3 position;"
	"layout(location = 1) in vec2 texCoord;"
	"out vec2 fragTexCoord;"
	"layout(location = 0) uniform mat4 matrixMVP;"

	"void main() {"
	"   fragTexCoord = texCoord;"
	"   gl_Position = matrixMVP * vec4(position, 1);"
	"}";

const std::string fragment_code =
	"#version 430 core\n"
	"in vec2 fragTexCoord;"
	"out vec4 fragColor;"
	"layout(location = 1) uniform sampler2D mainTexture;"

	"void main() {"
	"    fragColor = texture(mainTexture, fragTexCoord);"
	"}";


Scene::Scene() : mainCamera(nullptr) {
	if (activeScene == nullptr) activeScene = this;
	root = new SceneObject("root");
	renderer = new Renderer(Shader(vertex_code, fragment_code, "Standard Shader"));
}

Scene::~Scene() {
	delete root;
	delete renderer;
}

void Scene::addRootObject(SceneObject* object) {
	root->appendChild(object);
}

void Scene::setMainCamera(Camera* camera) {
	mainCamera = camera;
}

void Scene::makeActiveScene(){
	activeScene = this;
}

void Scene::render() {
	if (mainCamera == nullptr) {
		std::cout << "render: WARNING: No main camera assigned!" << std::endl;
		return;
	}

	glm::mat4 viewProjectionMatrix = mainCamera->getViewProjectionMatrix();
	
	std::stack<std::pair<const SceneObject*, glm::mat4>> objects;
	objects.push({ root, root->transform.getTransformMatrix() });

	glm::mat4 matrixMVP;
	while (!objects.empty()) {
		const auto& top = objects.top();

		const SceneObject* curObj = top.first;
		glm::mat4 globalTransform = top.second * curObj->transform.getTransformMatrix();

		objects.pop();

		matrixMVP = viewProjectionMatrix * globalTransform;
		std::vector<Renderable*> renderables = curObj->getComponents<Renderable>();
		for (Renderable* renderable : renderables) {
			renderer->drawObject(renderable->getRenderData(), matrixMVP);
		}

		// Simulate recursion propagating current global transform
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

Scene* Scene::getActiveScene() {
	return activeScene;
}
