#pragma once
#include "Camera.h"
#include "PointLight.h"
#include "AmbientLight.h"

#include "../graphics/Renderer.h"

class Scene {
private:
	friend class Renderable;	// FIXME: quick and dirty way to allow Renderable to access activeScene's renderer
	static Scene* activeScene;

	Camera* mainCamera;
	SceneObject* root;
	Renderer* renderer;

	bool isLightingEnabled;
	AmbientLight* ambientLight;
	std::vector<PointLight*> pointLights;	// TODO: call clear on destructor?

public:
	Scene();
	~Scene();

	void addRootObject(SceneObject* object);
	void setMainCamera(Camera* camera);
	void makeActiveScene();
	
	void addPointLight(PointLight* light);
	void setAmbientLight(AmbientLight* light);

	void render();
	void start();
	void update();

	void toggleDrawMode();
	void setLightingEnabled(bool value);

	static Scene* getActiveScene();
};