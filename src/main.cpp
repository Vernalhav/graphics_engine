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
#include "application/TransformFinder.h"
#include "application/Confiner.h"

namespace fs = std::filesystem;

Scene* setupScene() {
    Scene* scene = new Scene();

    SceneObject* mainCam = new SceneObject("mainCam");
    mainCam->addComponent<Camera>();
    mainCam->addComponent<FirstPersonController>();
    mainCam->addComponent<Controls>(mainCam->getComponent<Camera>());
    mainCam->addComponent<Confiner>(glm::vec2({-95, 95}), glm::vec2({-17, 40}), glm::vec2({-95, 95}));
    scene->setMainCamera(mainCam->getComponent<Camera>());

    SceneObject* house = new SceneObject("house");
    RenderData* houseRenderData = new RenderData("assets/models/minecraft_house/House_0.obj");
    house->transform.setScale(1);
    house->addComponent<Renderable>(houseRenderData);
    house->transform.setTranslation({ -1.04, -8.27, 58.8 });
    house->transform.setRotation({ 0, glm::half_pi<float>(), 0 });

    SceneObject* terrain = new SceneObject("terrain");
    RenderData* terrainRenderData = new RenderData("assets/models/minecraft_terrain/Mineways2Skfb.obj");
    terrain->transform.setScale(100);
    terrain->transform.translate({0, -50, 0});
    terrain->addComponent<Renderable>(terrainRenderData);

    SceneObject* sky = new SceneObject("skybox");
    RenderData* skyRenderData = new RenderData("assets/models/skybox/skycube.obj");
    sky->transform.setScale(1000);
    sky->addComponent<Renderable>(skyRenderData);

    scene->addRootObject(terrain);
    scene->addRootObject(house);
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

    delete scene;
    delete window;

    std::cout << "Terminating..." << std::endl;
    return EXIT_SUCCESS;
}
