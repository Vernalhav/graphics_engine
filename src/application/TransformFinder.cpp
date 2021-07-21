#include "TransformFinder.h"
#include "../engine/Input.h"
#include <iostream>
#include <iomanip>

TransformFinder::TransformFinder(SceneObject* obj)
	: Component(obj), sensitivity(0.1f), sensitivityModifier(100) { }

void TransformFinder::update() {
	glm::vec3 dir(0);

	if (Input::isKeyPressed(KeyCode::Up)) dir.x += 1;
	if (Input::isKeyPressed(KeyCode::Down)) dir.x -= 1;
	if (Input::isKeyPressed(KeyCode::Left)) dir.z -= 1;
	if (Input::isKeyPressed(KeyCode::Right)) dir.z += 1;
	if (Input::isKeyPressed(KeyCode::Ctrl)) dir.y -= 1;
	if (Input::isKeyPressed(KeyCode::Space)) dir.y += 1;

	dir *= sensitivity;
	if (Input::isKeyPressed(KeyCode::Shift))
		dir /= sensitivityModifier;

	sceneObject->transform.translate(dir);
	auto t = sceneObject->transform.getTranslation();
	std::cout << std::fixed << std::setprecision(2) << t.x << " " << t.y << " " << t.z << std::endl;
}
