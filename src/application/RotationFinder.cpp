#include "RotationFinder.h"
#include "../engine/Input.h"
#include <iostream>
#include <iomanip>

RotationFinder::RotationFinder(SceneObject* obj)
	: Component(obj), sensitivity(0.001f), sensitivityModifier(100) { }

void RotationFinder::update() {
	glm::vec3 dir(0);

	if (Input::isKeyPressed(KeyCode::Up)) dir.z += 1;
	if (Input::isKeyPressed(KeyCode::Down)) dir.z -= 1;
	if (Input::isKeyPressed(KeyCode::Left)) dir.x -= 1;
	if (Input::isKeyPressed(KeyCode::Right)) dir.x += 1;
	if (Input::isKeyPressed(KeyCode::Ctrl)) dir.y -= 1;
	if (Input::isKeyPressed(KeyCode::Space)) dir.y += 1;

	dir *= sensitivity;
	if (Input::isKeyPressed(KeyCode::Shift))
		dir /= sensitivityModifier;

	sceneObject->transform.rotate(dir);
	auto t = sceneObject->transform.getRotation();
	std::cout << std::fixed << std::setprecision(2) << t.x << " " << t.y << " " << t.z << std::endl;
}
