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

	void update();
	
	float getFov();
	float getNear();
	float getFar();

	void setFov(float fov);
	void setNear(float near);
	void setFar(float far);

	glm::mat4 getViewMatrix();
	glm::mat4 getOrtoghraphicMatrix();
	glm::mat4 getProjectionMatrix();
	glm::mat4 getViewProjectionMatrix();	// Returns projection * view
};

