#include "Scene.h"
#include <string.h>
#include <iostream>

const std::string vertex_code =
	"#version 430 core\n"
	"layout(location = 0) in vec3 position;"
	"layout(location = 1) in vec2 texCoord;"
	"out vec2 fragTexCoord;"
	"layout(location = 0) uniform mat4 model;"

	"void main() {"
	"   fragTexCoord = texCoord;"
	"   gl_Position = model * vec4(position, 1);"
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

void Scene::render() {
	if (mainCamera == nullptr) {
		std::cout << "render: WARNING: No main camera assigned!" << std::endl;
		return;
	}
}

void Scene::start() {
	root->start();
}

void Scene::update() {
	root->update();
}
