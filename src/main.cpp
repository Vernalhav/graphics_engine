#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "application/Color.h"
#include "application/FirstPersonController.h"
#include "application/TransformFinder.h"
#include "application/Confiner.h"

#include "engine/SceneObject.h"
#include "engine/PhysicsBody.h"
#include "engine/Scene.h"
#include "engine/Renderable.h"
#include "engine/Window.h"
#include "engine/Camera.h"

#include "misc/utils.h"
#include "engine/Input.h"
#include "application/Controls.h"


Scene* setupScene() {
    Scene* scene = new Scene();

    SceneObject* mainCam = new SceneObject("mainCam");
    mainCam->addComponent<Camera>();
    mainCam->addComponent<FirstPersonController>(false);
    mainCam->addComponent<Controls>(mainCam->getComponent<Camera>());
    mainCam->addComponent<Confiner>(glm::vec2({-100, 100}), glm::vec2({-17, 40}), glm::vec2({-100, 100}));
    scene->setMainCamera(mainCam->getComponent<Camera>());
    scene->addRootObject(mainCam);

    SceneObject* house = new SceneObject("house");
    RenderData* houseRenderData = new RenderData("assets/models/house/House_0.obj");
    house->addComponent<Renderable>(houseRenderData);
    house->transform.setTranslation({ -1.04, -8.27, 58.8 });
    house->transform.setRotation({ 0, glm::half_pi<float>(), 0 });
    scene->addRootObject(house);

    SceneObject* villager = new SceneObject("villager");
    RenderData* villagerRenderData = new RenderData("assets/models/villager/villager.obj");
    villager->transform.setScale(5);
    villager->transform.setTranslation({-4, -8.5, 0});
    villager->transform.setRotation({0, glm::radians(120.0f), 0});
    villager->addComponent<Renderable>(villagerRenderData);
    house->appendChild(villager);

    SceneObject* controller = new SceneObject("controller");
    RenderData* controllerRenderData = new RenderData("assets/models/controller/controller.obj");
    controller->addComponent<Renderable>(controllerRenderData);
    controller->transform.setScale(0.005f);
    controller->transform.setTranslation({ -1.33f, -10.65f, 4.6f });
    controller->transform.setRotation({ glm::pi<float>(), -glm::half_pi<float>(), 0 });
    house->appendChild(controller);

    SceneObject* terrain = new SceneObject("terrain");
    RenderData* terrainRenderData = new RenderData("assets/models/terrain/terrain.obj");
    terrain->transform.setScale(100);
    terrain->transform.translate({0, -50, 0});
    terrain->addComponent<Renderable>(terrainRenderData);
    scene->addRootObject(terrain);

    SceneObject* pond = new SceneObject("pond");
    RenderData* pondRenderData = new RenderData("assets/models/pond/pond.obj");
    pond->transform.setScale(20);
    pond->transform.translate({-34.53, -23.81f, 78.79f});
    pond->addComponent<Renderable>(pondRenderData);
    scene->addRootObject(pond);

    SceneObject* plant = new SceneObject("plant");
    RenderData* plantRenderData = new RenderData("assets/models/plant/plant.obj");
    plant->transform.setScale(0.05f);
    plant->transform.setTranslation({ 6.73f, -10, 5.7f });
    plant->addComponent<Renderable>(plantRenderData);
    house->appendChild(plant);

    SceneObject* sky = new SceneObject("skybox");
    RenderData* skyRenderData = new RenderData("assets/models/skybox/skycube.obj");
    sky->transform.setScale(1000);
    sky->addComponent<Renderable>(skyRenderData);
    scene->addRootObject(sky);

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
