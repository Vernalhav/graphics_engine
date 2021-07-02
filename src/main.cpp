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
        "#version 430 core\n"
        "layout(location = 0) in vec3 position;"
        "layout(location = 1) in vec2 texCoord;"
        "out vec2 fragTexCoord;"
        "layout(location = 0) uniform mat4 model;"
        
        "void main() {"
        "   fragTexCoord = texCoord;"
        "   gl_Position = model * vec4(position, 1);"
        "}";

    std::string fragment_code =
        "#version 430 core\n"
        "in vec2 fragTexCoord;"
        "out vec4 fragColor;"
        "layout(location = 1) uniform sampler2D mainTexture;"
        
        "void main() {"
        "    fragColor = texture(mainTexture, fragTexCoord);"
        "}";

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

    return scene;
}


int main() {
    
    GLFWwindow* window = initGLFW();
    Input::setWindow(window);

    //MeshRenderData* renderData = new MeshRenderData("assets/caixa.jpg");
    MeshRenderData* renderData = MeshLoader::loadMesh("assets/box.obj", "assets/caixa2.jpg");

    Transform transform;
    transform.scale = { 0.25f, 0.25f, 0.25f };
    Renderer* renderer = setupRenderer();
    renderer->uploadMesh(renderData);
    
    glm::vec3 backgroundColor = Color::CYAN / 255.0f;

    glfwShowWindow(window);
    glfwSetTime(0);

    //scene->start();

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, 1.0);

        Component::deltaTime = getDeltaTime();
        //scene->update();
        //renderer->drawObject(scene);
        transform.rotation[1] += 0.0001f;
        renderer->drawObject(renderData, transform);
 
        glfwSwapBuffers(window);
    }

    //delete scene;
    delete renderer;

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}
