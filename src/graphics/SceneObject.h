#pragma once

#include <map>
#include <stack>
#include <string>

#include "../math/vectors.h"
#include "Primitive.h"
#include "Transform.h"

class SceneObject;

class Component {
public:
	static double deltaTime;	// Populated by the main loop to indicate time between frames

	SceneObject* sceneObject;

	Component(SceneObject* obj) : sceneObject(obj) { }

	/// <summary>
	/// This function will be called every frame.
	/// Components should inherint from this class
	/// and implement their own update methods.
	/// </summary>
	virtual void update() = 0;

	virtual ~Component() { delete this; };

	static void setDeltaTime(double delta);

	template<typename Target>
	bool instanceof();
};

template<typename Target>
bool Component::instanceof() {
	return dynamic_cast<Target*>(this) != nullptr;
}


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
	std::vector<Component*> components;
	
public:
	Transform transform;

	SceneObject(std::string name, std::vector<Primitive>& p) : name(name), primitive(p) { }
	SceneObject(std::string name, std::vector<Primitive>&& p) : name(name), primitive(p) { }
	SceneObject(std::string name) : name(name), primitive() { }
	SceneObject() : name("unnamed object"), primitive() { }
	~SceneObject() {
		for (auto& child : children) delete child.second;
		components.clear();
	}

	void appendChild(SceneObject* child);

	void appendChildren(std::vector<SceneObject*> children);

	Transform& getTransform() { return transform; }
	
	const std::string& getName() const { return name; }
	
	const Transform& getTransform() const { return transform; }

	SceneObject* operator[](const std::string& name);
	SceneObject* child(const std::string& name);

	/// Adds a component to this SceneObject.
	/// ComponentType is the name of the Component subclass
	/// that will be added to this object. ...Args is a list
	/// of arguments that will be passed to ComponentType's
	/// constructor.
	/// 
	/// Usage examples:
	///		helicopter->addComponent<PhysicsBody>(1, 0.2);
	///		cloud->addComponent<Cloud>("my_cloud");
	/// in which 1 and 0.2 are the constructor parameters for
	/// the PhysicsBody component and "my_cloud" is the constructor
	/// parameter for the Cloud component.
	template<typename ComponentType, typename ...Args>
	inline void addComponent(Args ...args) {
		components.push_back(new ComponentType(this, args...));
	}

	template<typename ComponentType>
	ComponentType* getComponent();

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

template<typename ComponentType>
ComponentType* SceneObject::getComponent() {
	for (Component* component : components) {
		if (component->instanceof<ComponentType>()) {
			return (ComponentType*)component;
		}
	}

	return nullptr;
}