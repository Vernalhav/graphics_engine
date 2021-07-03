#pragma once

#include "SceneObject.h"

class Camera : public Component {
private:
	float fov;
	float zNear;
	float zFar;
	
	int screenWidth;
	int screenHeight;

public:
	Camera(SceneObject* obj);
	~Camera();

	void update();

	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();
	glm::mat4 getViewProjectionMatrix();	// Returns projection * view
};

