#include <iostream>

#include "SceneObject.h"

void SceneObject::appendChild(SceneObject* child) {
	if (children.count(child->name) != 0) {
		std::cout << "appendChild: WARNING: SceneObject " << name << " already has child " << child->name << std::endl;
		return;
	}
	children[child->name] = child;
}

void SceneObject::appendChildren(std::vector<SceneObject*> children) {
	for (auto child : children)
		appendChild(child);
}

SceneObject* SceneObject::operator[](const std::string& name) {
	return children[name];
}

SceneObject* SceneObject::child(const std::string& name) {
	return children[name];
}

/// <summary>
/// Returns the object's and all its children's
/// Primitives as a single array.
/// </summary>
/// <returns></returns>
std::vector<Primitive*> SceneObject::getObjectPrimitives() {
	std::vector<Primitive*> primitives;
	std::stack<SceneObject*> childrenStack;

	childrenStack.push(this);

	SceneObject* cur;
	while (!childrenStack.empty()) {
		cur = childrenStack.top();
		childrenStack.pop();

		for (const auto& child : cur->children) {
			childrenStack.push(child.second);
		}

		for (unsigned int i = 0; i < cur->primitive.size(); i++) {
			primitives.push_back(&(cur->primitive[i]));
		}
	}

	return primitives;
}

const std::vector<Primitive>& SceneObject::getObjectPrimitive() const {
	return primitive;
}

const std::vector<const SceneObject*> SceneObject::getChildren() const {
	std::vector<const SceneObject*> childrenArray;

	for (auto& childPair : children) {
		childrenArray.push_back((const SceneObject*)childPair.second);
	}

	return childrenArray;
}

void SceneObject::update() {
	physicsBody.updateTransform(transform);
	for (auto& child : children) {
		child.second->update();
	}
}
