#include <glm/glm.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "application/Color.h"

#include "engine/SceneObject.h"
#include "engine/PhysicsBody.h"
#include "engine/Scene.h"
#include "engine/Renderable.h"
#include "engine/Window.h"

#include "graphics/MeshLoader.h"
#include "misc/utils.h"


Scene* setupScene() {
    Scene* scene = new Scene();

    SceneObject* mainCam = new SceneObject("mainCam");
    mainCam->addComponent<Camera>();
    scene->setMainCamera(mainCam->getComponent<Camera>());

    SceneObject* box = new SceneObject("box");
    RenderData* renderData = MeshLoader::loadMesh("assets/box.obj", "assets/caixa.jpg");
    box->addComponent<Renderable>(renderData);
    box->addComponent<PhysicsBody>(glm::vec3({ 0, 0, 0 }), glm::vec3({ 0, 1, 0 }));

    scene->makeActiveScene();
    scene->addRootObject(box);
    scene->addRootObject(mainCam);

    mainCam->transform.translation = {0, 0, 10};

    return scene;
}

int main() {
    Window* window = new Window();

    Scene* scene = setupScene();

    glm::vec3 backgroundColor = Color::CYAN;

    window->show();

    scene->start();
    while (!window->shouldClose()) {
        Window::pollEvents();
        Window::clearBuffers();
        Window::setColor(backgroundColor);

        Component::deltaTime = Window::getDeltaTime();
        scene->update();
        scene->render();

        window->display();
    }

    window->close();
    Window::terminate();

    std::cout << "Terminating..." << std::endl;
    return EXIT_SUCCESS;
}
