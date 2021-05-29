#include <GL/glew.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <bitset>

#include "math/vectors.h"
#include "graphics/SceneObject.h"
#include "graphics/Shader.h"
#include "graphics/Renderer.h"
#include "graphics/PhysicsBody.h"
#include "misc/utils.h"
#include "object.h"

#define DEBUG 1

#ifdef DEBUG
#include "graphics/glDebugMessage.h"
#endif


GLFWwindow* window;


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


inline bool isKeyPressed(int key) {
    return glfwGetKey(window, key) == GLFW_PRESS;
}


void processInput(PhysicsBody* helicopterPB) {

    float linearAcceleration = 0.0005f;
    float angularAcceleration = 0.0005f;

    helicopterPB->kinematics.linearAcceleration = 0;
    helicopterPB->kinematics.angularAcceleration = 0;

    if (isKeyPressed(GLFW_KEY_W)) {
        helicopterPB->kinematics.linearAcceleration = linearAcceleration;
    }

    if (isKeyPressed(GLFW_KEY_A)) {
        helicopterPB->kinematics.angularAcceleration = angularAcceleration;
    }

    if (isKeyPressed(GLFW_KEY_D)) {
        helicopterPB->kinematics.angularAcceleration = -angularAcceleration;
    }
}

double getDeltaTime() {
    double delta = glfwGetTime();
    glfwSetTime(0);
    return delta;
}


int main(void) {
    window = initGLFW();

    // Setting up scene
    SceneObject* scene = new SceneObject("scene");
    SceneObject* helicopter = object::getHelicopter("player");
    scene->appendChild(helicopter);

    helicopter->transform.scale = 0.2f;
    helicopter->transform.translation = { -0.5f, 0 };
    helicopter->transform.rotation = PI / 4;

    PhysicsBody* helicopterPB = helicopter->getComponent<PhysicsBody>();

    // Getting renderer and uploading objects to GPU
    Renderer* renderer = setupRenderer();
    renderer->uploadObjects({ scene });
    
    glfwShowWindow(window);
    glfwSetTime(0);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0, 0.0, 0.0, 1.0);

        Component::setDeltaTime(getDeltaTime());
        processInput(helicopterPB);
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
