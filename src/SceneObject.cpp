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
std::vector<Primitive> SceneObject::getObjectPrimitives() {
	std::vector<Primitive> primitives;
	std::stack<SceneObject*> childrenStack;

	childrenStack.push(this);

	SceneObject* cur;
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