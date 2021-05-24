#pragma once

#include <map>
#include <stack>
#include <string>

#include "Primitive.h"
#include "Transform.h"
#include "PhysicsBody.h"
#include "vectors.h"


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
	Transform transform;
	PhysicsBody physicsBody;

	SceneObject(std::string name, std::vector<Primitive>& p) : name(name), primitive(p) { }
	SceneObject(std::string name, std::vector<Primitive>&& p) : name(name), primitive(p) { }
	SceneObject(std::string name) : name(name), primitive() { }
	SceneObject() : name("unnamed object"), primitive() { }
	~SceneObject() { for (auto& child : children) delete child.second; }

	void appendChild(SceneObject* child);

	void appendChildren(std::vector<SceneObject*> children);

	Transform& getTransform() { return transform; }
	
	const Transform& getTransform() const { return transform; }

	SceneObject* operator[](const std::string& name);
	SceneObject* child(const std::string& name);

	/// <summary>
	/// Returns the object's and all of its children's
	/// Primitives as a single array.
	/// </summary>
	/// <returns>Array with all Primitives</returns>
	std::vector<Primitive*> getObjectPrimitives();

	/// <summary>
	/// Returns the object's primitives that share the
	/// same transform.
	/// </summary>
	/// <returns>Array with object primitives</returns>
	const std::vector<Primitive>& getObjectPrimitive() const;

	const std::vector<const SceneObject*> getChildren() const;

	/// <summary>
	/// This funcion is called every frame.
	/// </summary>
	void update();
};