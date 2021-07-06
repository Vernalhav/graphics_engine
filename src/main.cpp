#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

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
#include "engine/FirstPersonController.h"
#include "engine/Camera.h"

#include "misc/utils.h"
#include "engine/Input.h"
#include "application/Controls.h"

#include <filesystem>

namespace fs = std::filesystem;

Scene* setupScene() {
    Scene* scene = new Scene();

    SceneObject* mainCam = new SceneObject("mainCam");
    mainCam->addComponent<Camera>();
    mainCam->addComponent<FirstPersonController>();
    mainCam->addComponent<Controls>(mainCam->getComponent<Camera>());
    mainCam->transform.setTranslation({ 0, 0, 0 });
    scene->setMainCamera(mainCam->getComponent<Camera>());

    SceneObject* house = new SceneObject("house");
    RenderData* houseRenderData = new RenderData("assets/models/house/casa.obj");
    house->transform.setScale(1);
    house->addComponent<Renderable>(houseRenderData);

    SceneObject* plant = new SceneObject("plant");
    RenderData* plantRenderData = new RenderData("assets/models/plant/plant.obj");
    plant->transform.setScale(1);
    plant->addComponent<Renderable>(plantRenderData);

    SceneObject* sky = new SceneObject("skybox");
    RenderData* skyRenderData = new RenderData("assets/models/skybox/skycube.obj");
    sky->transform.setScale(1000);
    sky->addComponent<Renderable>(skyRenderData);

    scene->addRootObject(house);
    scene->addRootObject(plant);
    scene->addRootObject(sky);
    scene->addRootObject(mainCam);
    return scene;
}

int main() {
    Window* window = new Window();

    Scene* scene = setupScene();
    glm::vec3 backgroundColor = Color::CYAN;
    window->show();

    scene->start();
    while (!window->shouldClose()) {
        window->pollEvents();
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
