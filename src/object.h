#pragma once
#include "graphics/SceneObject.h"

namespace Color {
	static Vector3 WHITE = {255, 255, 255};
	static Vector3 BLACK = {0, 0, 0};
	static Vector3 DARK_GRAY = {50, 50, 50};
	static Vector3 LIGHT_GRAY = {200, 200, 200};
	static Vector3 CYAN = {18, 135, 181};
}

class object {
public:
	static SceneObject* getHelicopter(const std::string& name, const Vector3& bodyColor = Color::WHITE, const Vector3& propellerColor = Color::LIGHT_GRAY);

	static SceneObject* getDrone(const std::string& name, const Vector3& bodyColor = Color::WHITE);

	static SceneObject* getSpinner();

	static SceneObject* getCloud(std::string name, Vector2 origin);

private:
	static std::vector<Primitive> getHelicopterBody(Vector3 color = Color::WHITE);

	static std::vector<Primitive> getPropeller(Vector3 color = Color::WHITE, float width = 0.1f, int nPropellers = 3);

	static std::vector<Vector3> getPolygon(int n, float rotation = 0, Vector3 offset = { 0, 0, 0 }, Vector2 scale = { 1, 1 });

	static std::vector<Vector3> getRectangle(float width, float length, float rotation);
};

