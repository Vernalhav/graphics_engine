#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "application/Color.h"

#include "engine/SceneObject.h"
#include "engine/PhysicsBody.h"
#include "engine/Input.h"
#include "engine/Scene.h"
#include "graphics/MeshLoader.h"
#include "graphics/Shader.h"
#include "graphics/Renderer.h"
#include "misc/utils.h"

#define DEBUG 1

#ifdef DEBUG
#include "graphics/glDebugMessage.h"
#endif
#include "engine/Renderable.h"


GLFWwindow* initGLFW() {
    glfwInit();

    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
#ifdef DEBUG
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif
    GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL Window", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    GLint GlewInitResult = glewInit();
    std::cout << "GlewStatus: " << glewGetErrorString(GlewInitResult) << std::endl;
    std::cout << "OpenGL version " << glGetString(GL_VERSION) << std::endl;
    
    glEnable(GL_DEPTH_TEST);

#ifdef DEBUG
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(GLDebugMessageCallback, NULL);
#endif
    return window;
}


/// <summary>
/// Calculate time in seconds between
/// the last getDeltaTime call.
/// </summary>
double getDeltaTime() {
    double delta = glfwGetTime();
    glfwSetTime(0);
    return delta;
}

Scene* setupScene() {
    Scene* scene = new Scene();

    SceneObject* mainCam = new SceneObject("mainCam");
    mainCam->addComponent<Camera>();
    scene->setMainCamera(mainCam->getComponent<Camera>());

    SceneObject* box = new SceneObject("box");
    RenderData* renderData = MeshLoader::loadMesh("assets/box.obj", "assets/caixa2.jpg");
    box->addComponent<Renderable>(renderData);
    box->addComponent<PhysicsBody>(glm::vec3({0, 0, 0 }), glm::vec3({ 0, 1, 0 }));

    scene->makeActiveScene();
    scene->addRootObject(box);
    scene->addRootObject(mainCam);

    mainCam->transform.translation = {0, 0, 10};

    return scene;
}

int main() {
    GLFWwindow* window = initGLFW();
    Input::setWindow(window);

    Scene* scene = setupScene();

    glm::vec3 backgroundColor = Color::CYAN / 255.0f;

    glfwShowWindow(window);
    glfwSetTime(0);

    scene->start();
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, 1.0);

        Component::deltaTime = getDeltaTime();
        scene->update();
        scene->render();

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}
