#include <GL/glew.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "Primitive.h"
#include "SceneObject.h"
#include "Shader.h"
#include "Renderer.h"
#include "vectors.h"
#include "object.h"
#include "utils.h"

#define DEBUG 1

#ifdef DEBUG
#include "glDebugMessage.h"
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

    return window;
}


int current_mouse = -1;
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (action == GLFW_RELEASE)
        current_mouse = -1;
    if (action == GLFW_PRESS)
        current_mouse = button;
}


int current_key = -1;
void key_press_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_RELEASE)
        current_key = -1;
    if (action == GLFW_PRESS)
        current_key = key;
}


void processInput(float& rotation, float& scale, float* translation) {

    float rotationPerFrame = 0.005f;
    float scalePerFrame = 0.005f;
    float TranslationPerFrame = 0.005f;

    switch (current_mouse) {
    case GLFW_MOUSE_BUTTON_1:
        scale += scalePerFrame;
        break;
    case GLFW_MOUSE_BUTTON_2:
        scale -= scalePerFrame;
        break;
    }

    switch (current_key) {
    case GLFW_KEY_W:
        translation[1] = std::min(translation[1] + TranslationPerFrame, 1.0f);
        break;
    case GLFW_KEY_A:
        translation[0] = std::max(translation[0] - TranslationPerFrame, -1.0f);
        break;
    case GLFW_KEY_S:
        translation[1] = std::max(translation[1] - TranslationPerFrame, -1.0f);
        break;
    case GLFW_KEY_D:
        translation[0] = std::min(translation[0] + TranslationPerFrame, 1.0f);
        break;

    case GLFW_KEY_LEFT:
        rotation += rotationPerFrame;
        break;
    case GLFW_KEY_RIGHT:
        rotation -= rotationPerFrame;
        break;
    }
}


int main(void) {
    GLFWwindow* window = initGLFW();
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetKeyCallback(window, key_press_callback);
    
#ifdef DEBUG
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(GLDebugMessageCallback, NULL);
#endif

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

    glDepthFunc(GL_LEQUAL);

    SceneObject* scene = new SceneObject("scene");
    SceneObject* helicopter = object::getHelicopter(0.5f);
    //SceneObject* helicopter = object::getSpinner();
    scene->appendChild(helicopter);

    Shader shader(vertex_code, fragment_code, "Standard shader");
    Renderer renderer(shader);
    renderer.uploadObjects({ scene });

    glfwShowWindow(window);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0, 0.0, 0.0, 1.0);

        scene->update();
        renderer.drawObject(scene);
 
        glfwSwapBuffers(window);
    }

    delete scene;

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}
