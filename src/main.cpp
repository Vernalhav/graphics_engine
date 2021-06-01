#include <GL/glew.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "math/vectors.h"
#include "engine/SceneObject.h"
#include "engine/PhysicsBody.h"
#include "engine/Input.h"
#include "graphics/Shader.h"
#include "graphics/Renderer.h"
#include "application/object.h"
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
        "uniform mat3 model;\n"
        "void main()\n"
        "{\n"
        "   vec3 computedPosition = model * position;"
        "   gl_Position = vec4(computedPosition.xy, 0, 1);\n"
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


double getDeltaTime() {
    double delta = glfwGetTime();
    glfwSetTime(0);
    return delta;
}


int main(void) {
    GLFWwindow* window = initGLFW();
    Input::setWindow(window);

    // Setting up scene
    SceneObject* scene = new SceneObject("scene");
    SceneObject* helicopter = object::getHelicopter("player");

    int numClouds = 5;
    for (int i = 0; i < numClouds; i++) {
        SceneObject* cloud = object::getCloud("cloud" + std::to_string(i),
            { utils::randRange(-1.0, 1.0), utils::randRange(-1.0, 1.0) });
        
        cloud->transform.scale = 0.1f;
        scene->appendChild(cloud);
    }
    
    scene->appendChild(helicopter);

    helicopter->transform.scale = 0.2f;

    SceneObject* drone = object::getDrone("drone");
    scene->appendChild(drone);

    PhysicsBody* helicopterPB = helicopter->getComponent<PhysicsBody>();

    // Getting renderer and uploading objects to GPU
    Renderer* renderer = setupRenderer();
    renderer->uploadObjects({ scene });
    
    Vector3 backgroundColor = Color::CYAN * (1 / 255.0f);

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
