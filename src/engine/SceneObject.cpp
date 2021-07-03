#include <iostream>

#include "SceneObject.h"


double Component::deltaTime;

void Component::update() { }

void Component::start() { }

void SceneObject::appendChild(SceneObject* child) {
	if (children.count(child->name) != 0) {
		std::cout << "appendChild: WARNING: SceneObject " << name << " already has child " << child->name << std::endl;
		return;
	}
	if (child->parent != nullptr) {
		// FIXME: Should add a removeChild method and remove child from the previous parent to mantain consistency
		std::cout << "appendChild: WARNING: SceneObject " << child->name << " already has a parent. " << \
						"Remove it before calling appendChild." << std::endl;
		return;
	}

	// FIXME: data duplication could allow for inconsistencies
	children[child->name] = child;
	child->parent = this;
}

void SceneObject::appendChildren(std::vector<SceneObject*> children) {
	for (auto child : children)
		appendChild(child);
}

glm::mat4 SceneObject::getGlobalTransform() {
	glm::mat4 globalTransform = transform;

	// FIXME: Possible endless loop if tree hierarchy is not enforced
	SceneObject* curAncestor = parent;
	while (curAncestor != nullptr) {
		globalTransform = curAncestor->transform.getTransformMatrix() * globalTransform;
		curAncestor = curAncestor->parent;
	}

	return globalTransform;
}

SceneObject* SceneObject::operator[](const std::string& name) {
	return children[name];
}

SceneObject* SceneObject::child(const std::string& name) {
	return children[name];
}

const std::vector<const SceneObject*> SceneObject::getChildren() const {
	std::vector<const SceneObject*> childrenArray;

	for (auto& childPair : children) {
		childrenArray.push_back((const SceneObject*)childPair.second);
	}

	return childrenArray;
}

void SceneObject::update() {
	for (Component* component : components) {
		component->update();
	}

	for (auto& child : children) {
		child.second->update();
	}
}

void SceneObject::start() {
	for (Component* component : components) {
		component->start();
	}

	for (auto& child : children) {
		child.second->start();
	}
}