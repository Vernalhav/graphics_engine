#pragma once
#include "SceneObject.h"

class object {
public:
	static SceneObject* getHelicopter(float scale = 0.5f);

private:
	static std::vector<Primitive> getHelicopterBody();

	static std::vector<Primitive> getPropeller(float width = 0.1, float length = 1, int nPropellers = 3);

	static std::vector<Vector3> getPolygon(int n, float rotation = 0.0, Vector3 offset = { 0, 0, 0 }, Vector2 scale = { 1, 1 });

	static std::vector<Vector3> getRectangle(float width, float length, float rotation);
};

