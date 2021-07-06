#pragma once
#include "Camera.h"
#include "../graphics/Renderer.h"

class Scene {
private:
	friend class Renderable;	// FIXME: quick and dirty way to allow Renderable to access activeScene's renderer
	static Scene* activeScene;

	Camera* mainCamera;
	SceneObject* root;
	Renderer* renderer;

public:
	Scene();
	~Scene();

	void addRootObject(SceneObject* object);
	void setMainCamera(Camera* camera);
	void makeActiveScene();
	
	void render();
	void start();
	void update();
	void toggleDrawMode();

	static Scene* getActiveScene();
};