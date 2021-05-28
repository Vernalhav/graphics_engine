#pragma once

#include "SceneObject.h"

class SceneObject;	// Declaring class here to avoid circular dependency

class Component {
public:
	SceneObject* sceneObject;

	Component(SceneObject* obj) : sceneObject(obj) { }

	/// <summary>
	/// This function will be called every frame.
	/// Components should inherint from this class
	/// and implement their own update methods.
	/// </summary>
	virtual void update() = 0;

	template<typename Target, typename T>
	bool instanceof() const {
		return dynamic_cast<const Target*>(this) != nullptr;
	}
};

/*
	Adding Components to ScenObjects (must inherit from Component)

	Intuitive implementation example:
	SceneObject* helicopter = object::getHelocopter();
	PhysicsBody* helicopter_pb = new PhysicsBody(helicopter, .....);
	helicopter->addComponent(helicopter_pb);

	Current API example (equivalent):
	SceneObject* helicopter = object::getHelocopter();
	helicopter->addComponent<PhysicsBody>(...);
*/