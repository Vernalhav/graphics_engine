#pragma once
#include "Camera.h"
#include "AmbientLight.h"
#include "PointLight.h"
#include "SpotLight.h"

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
	std::vector<SpotLight*> spotLights;		// TODO: call clear on destructor?

public:
	Scene();
	~Scene();

	void addRootObject(SceneObject* object);
	void setMainCamera(Camera* camera);
	void makeActiveScene();
	
	void addPointLight(PointLight* light);
	void addSpotLight(SpotLight* light);
	void setAmbientLight(AmbientLight* light);

	void render();
	void start();
	void update();

	void toggleDrawMode();
	void setLightingEnabled(bool value);

	static Scene* getActiveScene();
};