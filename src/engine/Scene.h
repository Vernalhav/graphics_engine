#pragma once
#include "Camera.h"
#include "../graphics/Renderer.h"

class Scene {
private:
	Camera* mainCamera;
	Renderer* renderer;
	SceneObject* root;

public:
	Scene();
	~Scene();

	void addRootObject(SceneObject* object);
	void setMainCamera(Camera* camera);
	void render();
	void start();
	void update();
};

