#pragma once
#include "SceneObject.h"

class object {
public:
	static SceneObject* getHelicopter(float scale = 0.5f);

	static SceneObject* getSpinner();

private:
	static std::vector<Primitive> getHelicopterBody();

	static std::vector<Primitive> getPropeller(Vector3 color = { 255, 255, 255 }, float width = 0.1f, int nPropellers = 3);

	static std::vector<Vector3> getPolygon(int n, float rotation = 0, Vector3 offset = { 0, 0, 0 }, Vector2 scale = { 1, 1 });

	static std::vector<Vector3> getRectangle(float width, float length, float rotation);
};

