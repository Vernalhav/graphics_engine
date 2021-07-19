#pragma once
#include "SceneObject.h"

class PointLight : public Component {
private:
	glm::vec3 diffuse;
	glm::vec3 attenuationCoefficients;

	/// <summary>
	/// Factor with which to dampen light intensity
	/// at the specified radius. i.e. a factor of 2
	/// means that objects at the radius will receive
	/// 1/2 light intensity.
	/// </summary>
	int attenuationAtRadius;
	float radius;

	void updateAttenuationCoefficients();

public:
	PointLight(SceneObject* obj, float radius = 1, int attenuationAtRadius = 10, const glm::vec3& diffuse = glm::vec3(1));

	void setRadius(float radius);
	void setAttenuationAtRadius(int attenuation);
};
