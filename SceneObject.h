#pragma once

#include <map>
#include <string>

#include "Primitive.h"


class SceneObject {
private:
	std::string name;

	Primitive primitive;
	std::map<std::string, SceneObject*> children;
	
public:
	std::pair<float, float> translation = { 0.0f, 0.0f };
	float rotation = 0;
	float scale = 1;

	SceneObject(std::string name, Primitive p) : name(name), primitive(p) { }

	SceneObject(std::string name) : name(name), primitive() { }

	SceneObject() : name("unnamed object"), primitive() { }

	void appendChild(SceneObject* child) {
		children[child->name] = child;
	}

	void appendChildren(std::vector<SceneObject*> children) {
		for (auto child : children)
			this->appendChild(child);
	}

	SceneObject* operator[](std::string str) {
		return this->children[str];
	}

	void draw() {

	}
};

/// <summary>
/// Uploads the scene objects' vertex data do the GPU
/// </summary>
/// <param name="objects"></param>
void uploadObjects(std::vector<SceneObject> objects) {

}