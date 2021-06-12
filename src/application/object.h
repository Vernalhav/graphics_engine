#pragma once
#include "../engine/SceneObject.h"

namespace Color {
	static glm::vec3 WHITE = {255, 255, 255};
	static glm::vec3 BLACK = {0, 0, 0};
	static glm::vec3 DARK_GRAY = {50, 50, 50};
	static glm::vec3 LIGHT_GRAY = {200, 200, 200};
	static glm::vec3 CYAN = {18, 135, 181};
}

class object {
public:
	static SceneObject* getHelicopter(const std::string& name, const glm::vec3& bodyColor = Color::WHITE, const glm::vec3& propellerColor = Color::LIGHT_GRAY);

	static SceneObject* getDrone(const std::string& name, const glm::vec3& bodyColor = Color::WHITE);

	static SceneObject* getSpinner();

	static SceneObject* getCloud(const std::string name, glm::vec2 origin);

	static SceneObject* getPlane(const std::string& name);

	static SceneObject* getSun(const std::string& name);

private:
	static std::vector<glm::vec3> getCrown(int nSpikes, float innerRadius, float outerRadius);

	static std::vector<Primitive> getHelicopterBody(glm::vec3 color = Color::WHITE);

	static std::vector<Primitive> getPropeller(glm::vec3 color = Color::WHITE, float width = 0.1f, int nPropellers = 3);

	static std::vector<glm::vec3> getPolygon(int n, float rotation = 0, glm::vec3 offset = { 0, 0, 0 }, glm::vec2 scale = { 1, 1 });

	static std::vector<glm::vec3> getRectangle(float width, float length, float rotation);
};

