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
#include "graphics/MeshLoader.h"
#include "graphics/Shader.h"
#include "graphics/Renderer.h"
#include "misc/utils.h"

#define DEBUG 1

#ifdef DEBUG
#include "graphics/glDebugMessage.h"
#endif


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


Renderer* setupRenderer() {
    std::string vertex_code =
        "#version 150\n"
        "in vec3 position;\n"
        "uniform mat4 model;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = model * vec4(position, 1);\n"
        "}\n";

    std::string fragment_code =
        "#version 150\n"
        "uniform vec4 color;\n"
        "void main()\n"
        "{\n"
        "    gl_FragColor = color;\n"
        "}\n";

    Shader shader(vertex_code, fragment_code, "Standard shader");
    return new Renderer(shader);
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


/// <summary>
/// Creates, configures and lays out all scene objects
/// in the scene hierarchy. Returns parent SceneObject
/// to which all root-level objects will be parented to.
/// </summary>
SceneObject* setupScene() {
    SceneObject* scene = new SceneObject("scene");

    Primitive base = {
        {{+0.5f, +0.0f, +0.5f},
         {+0.5f, +0.0f, -0.5f},
         {-0.5f, +0.0f, +0.5f},
         {-0.5f, +0.0f, -0.5f}},
         GL_TRIANGLE_STRIP, Color::BLACK };
 
    Primitive face1 = {
        {{+0.5f, +0.0f, +0.5f},
         {+0.5f, +0.0f, -0.5f},
         {+0.0f, +1.0f, +0.0f}},
         GL_TRIANGLE_FAN, Color::GREEN };

    Primitive face2 = {
        {{+0.5f, +0.0f, +0.5f},
         {-0.5f, +0.0f, +0.5f},
         {+0.0f, +1.0f, +0.0f}},
         GL_TRIANGLE_FAN, Color::BLUE };

    Primitive face3 = {
        {{-0.5f, +0.0f, -0.5f},
         {-0.5f, +0.0f, +0.5f},
         {+0.0f, +1.0f, +0.0f}},
         GL_TRIANGLE_FAN, Color::RED };

    Primitive face4 = {
        {{-0.5f, +0.0f, -0.5f},
         {+0.5f, +0.0f, -0.5f},
         {+0.0f, +1.0f, +0.0f}},
         GL_TRIANGLE_FAN, Color::WHITE };

    SceneObject* pyramid = new SceneObject("pyramid", {base, face1, face2, face3, face4});
    pyramid->transform.translation.y = -0.25;
    pyramid->addComponent<PhysicsBody>(glm::vec3(0), glm::vec3(PI, PI, PI));

    Mesh* box = MeshLoader::loadMesh("assets/box.obj");
    delete box;

    scene->appendChild(pyramid);
    return scene;
}


int main() {
    GLFWwindow* window = initGLFW();
    Input::setWindow(window);

    SceneObject* scene = setupScene();

    // Getting renderer and uploading objects to GPU
    Renderer* renderer = setupRenderer();
    renderer->uploadObjects({ scene });
    
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
        renderer->drawObject(scene);
 
        glfwSwapBuffers(window);
    }

    delete scene;
    delete renderer;

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}
