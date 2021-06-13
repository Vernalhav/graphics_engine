#pragma once

#include <glm/glm.hpp>
#include <map>
#include <stack>
#include <string>

#include "../graphics/Primitive.h"
#include "Transform.h"

class SceneObject;

class Component {
public:
	static double deltaTime;	// Populated by the main loop to indicate time between frames

	SceneObject* sceneObject;

	Component(SceneObject* obj) : sceneObject(obj) { }

	/// <summary>
	/// This function will be called every frame.
	/// Components can inherint from this class
	/// and implement their own update methods.
	/// </summary>
	virtual void update();

	/// <summary>
	/// This function will be called before the
	/// main loop starts. Components can inherit
	/// from this class and implement their own
	/// start methods.
	/// </summary>
	virtual void start();

	virtual ~Component() = default;

	template<typename Target>
	bool instanceof();
};


class SceneObject {
private:
	std::string name;

	/// <summary>
	/// Vector of primitives that should represent a semantic object, for instance
	/// 4 rectangles forming a windmill. The collection of these primitives will
	/// share a single Transform.
	/// </summary>
	std::vector<Primitive> primitive;

	/// <summary>
	/// Mapping between the name of each children of this SceneObject and
	/// its corresponding object pointer.
	/// </summary>
	std::map<std::string, SceneObject*> children;

	/// <summary>
	/// Array of Components attached to this SceneObject
	/// that will initialized and updated each frame.
	/// </summary>
	std::vector<Component*> components;

public:
	Transform transform;

	SceneObject(std::string name, std::vector<Primitive>& p) : name(name), primitive(p), transform() { }
	SceneObject(std::string name, std::vector<Primitive>&& p) : name(name), primitive(p), transform() { }
	SceneObject(std::string name) : name(name), primitive(), transform() { }
	SceneObject() : name("unnamed object"), primitive(), transform() { }
	~SceneObject() {
		for (auto& child : children) delete child.second;
		components.clear();
	}

	// Changes the color of the object's Primitives.
	void setPrimitiveColor(glm::vec3 color);
	// Changes the color of the object's Primitive at the index provided.
	void setPrimitiveColor(glm::vec3 color, int index);

	// Adds child as a child of the current SceneObject.
	void appendChild(SceneObject* child);
	void appendChildren(std::vector<SceneObject*> children);

	const std::string& getName() const { return name; }
	
	const Transform& getTransform() const { return transform; }
	Transform& getTransform() { return transform; }

	SceneObject* operator[](const std::string& name);
	SceneObject* child(const std::string& name);

	/// Adds a component to this SceneObject.
	/// ComponentType is the name of the Component subclass
	/// that will be added to this object. ...args is a list
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
		components.push_back(new ComponentType(this, std::forward<Args>(args)...));
	}

	/// <summary>
	/// Returns a component attached to the current
	/// SceneObject that matches the template parameter.
	/// If there are none, returns nullptr.
	/// </summary>
	/// <typeparam name="ComponentType">Type of component to search for</typeparam>
	/// <returns>Pointer to the Component</returns>
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

	/// <summary>
	/// Returns all of the object's immediate children
	/// </summary>
	/// <returns>Array of pointers to the children SceneObjects</returns>
	const std::vector<const SceneObject*> getChildren() const;

	/// <summary>
	/// Updates every component attached to this object
	/// by calling their update methods.
	/// </summary>
	void update();

	/// <summary>
	/// Initializes every component attached to this object
	/// by calling their start methods.
	/// </summary>
	void start();
};


template<typename Target>
bool Component::instanceof() {
	return dynamic_cast<Target*>(this) != nullptr;
}


template<typename ComponentType>
ComponentType* SceneObject::getComponent() {
	for (Component* component : components) {
		if (component->instanceof<ComponentType>()) {
			return reinterpret_cast<ComponentType*>(component);
		}
	}

	return nullptr;
}