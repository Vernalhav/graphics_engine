#pragma once

#include <map>
#include <string>

#include "Primitive.h"


class SceneObject {
private:

	std::pair<float, float> translation;
	float rotation;
	float scale;

	Primitive primitive;
	std::map<std::string, SceneObject*> children;



public:
	SceneObject* operator[](std::string str) {
		return this->children[str];
	}
};

struct Transform {
	
};