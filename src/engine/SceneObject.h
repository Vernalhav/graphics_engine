#pragma once

#include <glm/glm.hpp>
#include <map>
#include <stack>
#include <string>
#include <vector>

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
	SceneObject* parent;

	SceneObject(const std::string& name) : name(name), transform(), parent(nullptr) { }
	SceneObject() : name("unnamed object"), transform(), parent(nullptr) { }
	~SceneObject() {
		for (auto& child : children) delete child.second;
		components.clear();
	}

	// Adds child as a child of the current SceneObject.
	void appendChild(SceneObject* child);
	void appendChildren(std::vector<SceneObject*> children);

	std::string getName() const { return name; }
	
	Transform getTransform() { return transform; }

	/// <summary>
	/// Returns 4x4 transformation matrix that
	/// is the composition of this object and all
	/// of its parents' Transforms.
	/// </summary>
	glm::mat4 getGlobalTransform();

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
	void addComponent(Args ...args);

	/// <summary>
	/// Returns the first component attached to the current
	/// SceneObject that matches the template parameter.
	/// If there are none, returns nullptr.
	/// </summary>
	/// <typeparam name="ComponentType">Type of component to search for</typeparam>
	/// <returns>Pointer to the Component</returns>
	template<typename ComponentType>
	ComponentType* getComponent();

	/// <summary>
	/// Returns all components attached to the current
	/// SceneObject that match the template parameter.
	/// If there are none, returns an empty array.
	/// </summary>
	/// <typeparam name="ComponentType">Type of component to search for</typeparam>
	/// <returns>Array with the Components in the same order that they haeve been added</returns>
	template<typename ComponentType>
	std::vector<ComponentType*> getComponents() const;

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


template<typename ComponentType, typename ...Args>
inline void SceneObject::addComponent(Args ...args) {
	components.push_back(new ComponentType(this, std::forward<Args>(args)...));
}


template<typename Target>
inline bool Component::instanceof() {
	return dynamic_cast<Target*>(this) != nullptr;
}


template<typename ComponentType>
inline ComponentType* SceneObject::getComponent() {
	for (Component* component : components) {
		if (component->instanceof<ComponentType>()) {
			return reinterpret_cast<ComponentType*>(component);
		}
	}

	return nullptr;
}

template<typename ComponentType>
inline std::vector<ComponentType*> SceneObject::getComponents() const {
	std::vector<ComponentType*> matches;
	for (Component* component : components) {
		if (component->instanceof<ComponentType>()) {
			matches.push_back(reinterpret_cast<ComponentType*>(component));
		}
	}
	return matches;
}
