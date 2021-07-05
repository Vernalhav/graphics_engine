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

#include "graphics/MeshLoader.h"
#include "misc/utils.h"
#include "engine/Input.h"


Scene* setupScene() {
    Scene* scene = new Scene();

    SceneObject* mainCam = new SceneObject("mainCam");
    mainCam->addComponent<Camera>();
    mainCam->addComponent<FirstPersonController>();
    mainCam->transform.setTranslation({ 0, 0, 0 });
    scene->setMainCamera(mainCam->getComponent<Camera>());

    SceneObject* house = new SceneObject("house");
    RenderData* houseRenderData = MeshLoader::loadMesh("assets/casa.obj", "assets/casa.jpg");
    house->transform.setScale(1);
    house->addComponent<Renderable>(houseRenderData);

    SceneObject* sky = new SceneObject("skybox");
    RenderData* skyRenderData = MeshLoader::loadMesh("assets/skycube.obj", "assets/bluesunset_skybox.png");
    sky->transform.setScale(1000);
    sky->addComponent<Renderable>(skyRenderData);

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

    std::cout << "Terminating..." << std::endl;
    return EXIT_SUCCESS;
}
