#include "Window.h"
#include "../graphics/glDebugMessage.h"

#include <gl/glew.h>
#include <iostream>

#define DEBUG 1;

Window* Window::activeWindow = nullptr;


void initWindowSystem() {
    glfwInit();
}

void initGraphicsContext() {
    GLint GlewInitResult = glewInit();

    std::cout << "GlewStatus: " << glewGetErrorString(GlewInitResult) << std::endl;
    std::cout << "OpenGL version " << glGetString(GL_VERSION) << std::endl;

    glEnable(GL_DEPTH_TEST);

#ifdef DEBUG
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(GLDebugMessageCallback, NULL);
#endif
}

void onMouseButtonPressed(GLFWwindow* window, int button, int action, int mods) {
    Window* winObject = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
    if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_1) {
        winObject->captureMouseCursor();
    }
}

void onKeyPressed(GLFWwindow* window, int key, int scancode, int action, int mods) {
    Window* winObject = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
    if (action == GLFW_PRESS && key == GLFW_KEY_ESCAPE) {
        winObject->releaseMouseCursor();
    }
}

void onResize(GLFWwindow* window, int width, int height) {
    Window* winObject = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
    int w, h;
    winObject->getWindowSize(w, h);
    glViewport(0, 0, w, h);
}

void Window::captureMouseCursor() {
    setActive();

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    if (glfwRawMouseMotionSupported()) {
        glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    }
}

void Window::releaseMouseCursor() {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    if (glfwRawMouseMotionSupported()) {
        glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_FALSE);
    }
}

void Window::setActive() {
    glfwMakeContextCurrent(window);
    activeWindow = this;
}

bool Window::shouldClose() {
    return glfwWindowShouldClose(window);
}

void Window::show() {
    glfwShowWindow(window);
}

void Window::close() {
    glfwDestroyWindow(window);
}

void Window::display() {
    glfwSwapBuffers(window);
}

void Window::getWindowSize(int& width, int& height) {
    glfwGetFramebufferSize(window, &width, &height);
}

bool Window::isKeyPressed(int keyCode) {
    return glfwGetKey(window, keyCode) == GLFW_PRESS;
}

void Window::pollEvents() {
    glfwPollEvents();
}

void Window::clearBuffers() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::setColor(const glm::vec3& color) {
    glClearColor(color.x / 255.0f, color.y / 255.0f, color.z / 255.0f, 1.0);
}

double Window::getDeltaTime() {
    double delta = glfwGetTime();
    glfwSetTime(0);
    return delta;
}

void Window::getActiveWindowSize(int& width, int& height) {
    activeWindow->getWindowSize(width, height);
}

void Window::terminate() {
    glfwTerminate();
}

Window::Window(int width, int height, const std::string& name) {
	if (activeWindow == nullptr) {
		initWindowSystem();
	}

    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
    glfwSetWindowUserPointer(window, (void *)this);

    glfwSetKeyCallback(window, onKeyPressed);
    glfwSetMouseButtonCallback(window, onMouseButtonPressed);
    glfwSetWindowSizeCallback(window, onResize);
    glfwMakeContextCurrent(window);
    glfwSetTime(0);
    
    if (activeWindow == nullptr) {
        initGraphicsContext();
    }

    setActive();
}

Window::~Window() { }
