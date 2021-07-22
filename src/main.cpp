#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "application/Color.h"
#include "application/FirstPersonController.h"
#include "application/TransformFinder.h"
#include "application/Confiner.h"
#include "application/Controls.h"
#include "application/SinMovement.h"
#include "application/Ghast.h"
#include "application/RotationFinder.h"

#include "engine/SceneObject.h"
#include "engine/PhysicsBody.h"
#include "engine/Scene.h"
#include "engine/Renderable.h"
#include "engine/Window.h"
#include "engine/Camera.h"
#include "engine/Input.h"

#include "misc/utils.h"
#include "engine/AmbientLight.h"
#include "engine/PointLight.h"


SceneObject* getQuadLight(const std::string& name, const glm::vec3& lightColor = Color::WHITE, float subLightRadius = 1.0f) {
    SceneObject* quadLight = new SceneObject(name);
    const glm::vec3 lightIntensity = lightColor / 255.0f;

    constexpr float angleStep = glm::half_pi<float>();

    for (int i = 0; i < 4; i++) {
        SceneObject* subLight = new SceneObject(name + "_subLight_" + std::to_string(i));
        subLight->addComponent<PointLight>(12.0f, 20, lightIntensity);
        quadLight->appendChild(subLight);
        subLight->transform.translate(glm::vec3(glm::cos(i * angleStep), 0, glm::sin(i * angleStep)) * subLightRadius);
    }

    return quadLight;
}

Scene* setupScene() {
    Scene* scene = new Scene();

    SceneObject* ambientLight = new SceneObject("ambient");
    ambientLight->addComponent<AmbientLight>(0.2f);
    scene->addRootObject(ambientLight);

    SceneObject* mainCam = new SceneObject("mainCam");
    mainCam->addComponent<Camera>();
    mainCam->addComponent<PointLight>(20.0f);
    mainCam->addComponent<FirstPersonController>(false, 0.15f);
    mainCam->addComponent<Controls>(mainCam->getComponent<Camera>(), ambientLight->getComponent<AmbientLight>());
    mainCam->addComponent<Confiner>(glm::vec2({-100, 100}), glm::vec2({-17, 60}), glm::vec2({-100, 100}));
    mainCam->transform.setTranslation({0, -17, 0});
    scene->setMainCamera(mainCam->getComponent<Camera>());
    scene->addRootObject(mainCam);

    SceneObject* torchLight1 = getQuadLight("torchLight1", Color::FIRE_ORANGE);
    torchLight1->transform.translate({ -3.6f, -17, 58.2f });
    scene->addRootObject(torchLight1);

    SceneObject* torchLight2 = getQuadLight("torchLight2", Color::FIRE_ORANGE);
    torchLight2->transform.translate({ -2.8f, -8.9f, 53.7f });
    scene->addRootObject(torchLight2);

    SceneObject* torchLight3 = getQuadLight("torchLight3", Color::FIRE_ORANGE);
    torchLight3->transform.translate({ -0.5f, -8.9f, 67.7f });
    scene->addRootObject(torchLight3);

    SceneObject* externalTorchLight1 = getQuadLight("externalTorchLight1", Color::FIRE_ORANGE);
    externalTorchLight1->transform.translate({ -13.1f, -8.9f, 71.6f });
    scene->addRootObject(externalTorchLight1);

    SceneObject* externalTorchLight2 = getQuadLight("externalTorchLight2", Color::FIRE_ORANGE);
    externalTorchLight2->transform.translate({ -13.1f, -8.9f, 52.0f });
    scene->addRootObject(externalTorchLight2);

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

    SceneObject* balloon = new SceneObject("balloon");
    SceneObject* balloonPivot = new SceneObject("balloonPivot");
    RenderData* balloonRenderData = new RenderData("assets/models/balloon/balloon.obj");
    balloon->addComponent<PointLight>(50.0f);
    balloon->addComponent<Renderable>(balloonRenderData);
    balloon->addComponent<SinMovement>(0.02f, 1.0f);
    balloon->transform.setTranslation({0, 0, 40});  // rotation radius
    balloon->transform.setScale(30);
    balloonPivot->addComponent<PhysicsBody>(glm::vec3(0), glm::vec3({ 0, 0.3, 0 }));
    balloonPivot->appendChild(balloon);
    balloonPivot->transform.setTranslation({-0.7f, 30, 62.2f});
    scene->addRootObject(balloonPivot);

    SceneObject* steve = new SceneObject("steve");
    RenderData* steveRenderData = new RenderData("assets/models/steve/steve.obj");
    steve->addComponent<Renderable>(steveRenderData);
    steve->transform.setScale(0.25f);
    steve->transform.setTranslation({0.4f, 0.20f, -0.81f});
    steve->transform.setRotation({0, glm::radians(200.0f), 0});
    pond->appendChild(steve);

    SceneObject* guitar = new SceneObject("guitar");
    RenderData* guitarRenderData = new RenderData("assets/models/guitar/guitar.obj");
    guitar->addComponent<Renderable>(guitarRenderData);
    guitar->transform.setScale(0.1f);
    guitar->transform.setTranslation({0.24f, 0.22f, -0.68f});
    guitar->transform.setRotation({ 1.33f, 4.64f, 1.16f });
    pond->appendChild(guitar);

    SceneObject* ghast = new SceneObject("ghast");
    RenderData* ghastRenderData = new RenderData("assets/models/ghast/ghast.obj");
    ghast->transform.setScale(8);
    ghast->transform.translate({ 20, 0, 10 });
    ghast->addComponent<Renderable>(ghastRenderData);
    ghast->addComponent<Ghast>();
    ghast->addComponent<Confiner>(glm::vec2(-90, 90), glm::vec2(-10, 90), glm::vec2(-90, 90));
    ghast->addComponent<SinMovement>(0.002f, 0.8f);
    scene->addRootObject(ghast);

    SceneObject* plant = new SceneObject("plant");
    RenderData* plantRenderData = new RenderData("assets/models/plant/plant.obj");
    plant->transform.setScale(0.05f);
    plant->transform.setTranslation({ 6.73f, -10, 5.7f });
    plant->addComponent<Renderable>(plantRenderData);
    house->appendChild(plant);

    RenderData* lampRenderData = new RenderData("assets/models/lamp/lamp.obj");

    SceneObject* lamp1 = new SceneObject("lamp1");
    SceneObject* lamp1Light = getQuadLight("lamp1Light", Color::ICE_BLUE, 4.0f);
    lamp1Light->transform.translate({ 0, 26.0f, 0.0f });
    lamp1->addComponent<Renderable>(lampRenderData);
    lamp1->transform.setScale(0.015f);
    lamp1->transform.translate({ -0.32f, 0, -0.7f });
    lamp1->appendChild(lamp1Light);
    pond->appendChild(lamp1);

    SceneObject* lamp2 = new SceneObject("lamp2");
    SceneObject* lamp2Light = getQuadLight("lamp2Light", Color::ICE_BLUE, 4.0f);
    lamp2Light->transform.translate({ 0, 26.0f, 0.0f });
    lamp2->addComponent<Renderable>(lampRenderData);
    lamp2->transform.setScale(0.015f);
    lamp2->transform.translate({ 0.52f, 0, -0.7f });
    lamp2->appendChild(lamp2Light);
    pond->appendChild(lamp2);

    SceneObject* sky = new SceneObject("skybox");
    RenderData* skyRenderData = new RenderData("assets/models/skybox/skycube.obj");
    sky->transform.setScale(1000);
    sky->addComponent<Renderable>(skyRenderData);
    scene->addRootObject(sky);

    return scene;
}

Scene* setupTestScene() {
    Scene* scene = new Scene();

    SceneObject* mainCam = new SceneObject("mainCam");
    mainCam->addComponent<Camera>();
    //mainCam->addComponent<PointLight>(20.0f);
    mainCam->addComponent<FirstPersonController>(false, 2.0f);
    mainCam->addComponent<Controls>(mainCam->getComponent<Camera>());
    scene->setMainCamera(mainCam->getComponent<Camera>());
    scene->addRootObject(mainCam);

    SceneObject* sky = new SceneObject("skybox");
    RenderData* skyRenderData = new RenderData("assets/models/skybox/skycube.obj");
    sky->transform.setScale(1000);
    sky->addComponent<Renderable>(skyRenderData);
    scene->addRootObject(sky);

    SceneObject* plant = new SceneObject("plant");
    RenderData* plantRenderData = new RenderData("assets/models/plant/plant.obj");
    plant->addComponent<Renderable>(plantRenderData);
    scene->addRootObject(plant);

    SceneObject* light = new SceneObject("light");
    light->addComponent<PointLight>(40.0f);
    light->transform.translate({3.2f, 4.5f, 14.4f});
    scene->addRootObject(light);

    SceneObject* ambientLight = new SceneObject("ambient");
    ambientLight->addComponent<AmbientLight>(0.2f);
    scene->addRootObject(ambientLight);

    return scene;
}

int main() {

    std::ios_base::sync_with_stdio(false);
    glm::vec3 backgroundColor = Color::BLACK;

    Window* window = new Window();
    Scene* scene = setupScene();
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
