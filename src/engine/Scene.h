#pragma once
#include "Camera.h"
#include "../graphics/Renderer.h"

class Scene {
private:
	Camera* mainCamera;
	SceneObject* root;
	static Scene* activeScene;
	Renderer* renderer;
	friend class Renderable;	// FIXME: quick and dirty way to allow Renderable to access activeScene's renderer

public:
	Scene();
	~Scene();

	void addRootObject(SceneObject* object);
	void setMainCamera(Camera* camera);
	void makeActiveScene();
	
	void render();
	void start();
	void update();

	static Scene* getActiveScene();
};

