#include "SceneObject.h"


void SceneObject::appendChild(SceneObject* child) {
	children[child->name] = child;
}

void SceneObject::appendChildren(std::vector<SceneObject*> children) {
	for (auto child : children)
		this->appendChild(child);
}

SceneObject* SceneObject::operator[](std::string str) {
	return this->children[str];
}

/// <summary>
/// Returns the object's and all its children's
/// Primitives as a single array.
/// </summary>
/// <returns></returns>
std::vector<Primitive> SceneObject::getObjectPrimitives() const {
	std::vector<Primitive> primitives;
	std::stack<const SceneObject*> childrenStack;

	childrenStack.push(this);

	const SceneObject* cur;
	while (!childrenStack.empty()) {
		cur = childrenStack.top();
		childrenStack.pop();

		for (const auto& child : children) {
			childrenStack.push(child.second);
		}

		primitives.insert(primitives.end(), cur->primitive.begin(), cur->primitive.end());
	}

	return primitives;
}

const std::vector<Primitive>& SceneObject::getObjectPrimitive() const {
	return this->primitive;
}

const std::vector<const SceneObject*> SceneObject::getChildren() const {
	std::vector<const SceneObject*> childrenArray;

	for (auto& childPair : children) {
		childrenArray.push_back((const SceneObject*)childPair.second);
	}

	return childrenArray;
}
