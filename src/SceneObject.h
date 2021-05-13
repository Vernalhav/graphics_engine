#pragma once

#include <map>
#include <stack>
#include <string>

#include "Primitive.h"


class SceneObject {
private:
	std::string name;

	/// <summary>
	/// Vector of primitives that should represent a semantic object, for instance
	/// 4 rectangles forming a windmill. The collection of these primitives will
	/// share a single Transform.
	/// </summary>
	std::vector<Primitive> primitive;
	std::map<std::string, SceneObject*> children;
	
public:
	std::pair<float, float> translation = { 0.0f, 0.0f };
	float rotation = 0;
	float scale = 1;

	SceneObject(std::string name, std::vector<Primitive>& p) : name(name), primitive(p) { }
	SceneObject(std::string name, std::vector<Primitive>&& p) : name(name), primitive(p) { }
	SceneObject(std::string name) : name(name), primitive() { }
	SceneObject() : name("unnamed object"), primitive() { }
	~SceneObject() { for (auto& child : children) delete child.second; }

	void appendChild(SceneObject* child);

	void appendChildren(std::vector<SceneObject*> children);

	SceneObject* operator[](std::string str);

	/// <summary>
	/// Returns the object's and all of its children's
	/// Primitives as a single array.
	/// </summary>
	/// <returns>Array with all Primitives</returns>
	std::vector<Primitive> getObjectPrimitives();
};