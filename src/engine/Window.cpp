#include "Window.h"
#include "../graphics/glDebugMessage.h"

#include <gl/glew.h>
#include <iostream>

#define DEBUG 1;

Window* Window::activeWindow = nullptr;


class WindowCallbacks {
public:
    static void onMouseButtonPressed(GLFWwindow* window, int button, int action, int mods) {
        Window* winObject = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
        if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_1) {
            winObject->captureMouseCursor();
            winObject->setActive();
        }

        MouseButton btn = Input::convertMouseButton(button);
        ActionState state = Input::convertActionState(action);
        winObject->onMouseButtonClick(btn, state);
    }

    static void onKeyPressed(GLFWwindow* window, int key, int scancode, int action, int mods) {
        Window* winObject = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
        if (action == GLFW_PRESS && key == GLFW_KEY_ESCAPE) {
            winObject->releaseMouseCursor();
            Window::activeWindow = nullptr;
        }

        KeyCode pressedKey = Input::convertKeyCode(key);
        ActionState state = Input::convertActionState(action);
        winObject->onKeyPress(pressedKey, state);
    }


    static void onScroll(GLFWwindow* window, double x, double y) {
        Window* winObject = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
        winObject->onScroll((float)y);
    }

    static void onResize(GLFWwindow* window, int width, int height) {
        Window* winObject = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
        int w, h;
        winObject->getWindowSize(w, h);
        glViewport(0, 0, w, h);
    }

    static void onWindowChangeFocus(GLFWwindow* window, int focused) {
        Window* winObject = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
        if (focused == GLFW_TRUE) {
            winObject->captureMouseCursor();
            winObject->setActive();
        }
        else {
            winObject->releaseMouseCursor();
            Window::activeWindow = nullptr;
        }
    }
};

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

Window::Window(int width, int height, const std::string& name)
    : lastX(0), lastY(0), dx(0), dy(0) {

    if (activeWindow == nullptr) {
        initWindowSystem();
    }

    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
    glfwSetWindowUserPointer(window, (void*)this);

    glfwSetKeyCallback(window, WindowCallbacks::onKeyPressed);
    glfwSetMouseButtonCallback(window, WindowCallbacks::onMouseButtonPressed);
    glfwSetScrollCallback(window, WindowCallbacks::onScroll);
    glfwSetWindowSizeCallback(window, WindowCallbacks::onResize);
    glfwSetWindowFocusCallback(window, WindowCallbacks::onWindowChangeFocus);

    glfwMakeContextCurrent(window);
    glfwSetTime(0);

    if (activeWindow == nullptr) {
        initGraphicsContext();
    }

    setActive();
}

void Window::setActive() {
    glfwMakeContextCurrent(window);
    activeWindow = this;
}

void Window::addKeyListener(KeyPressListener* listener) {
    keyPressListeners.push_back(listener);
}

void Window::addMouseButtonListener(MouseButtonListener* listener) {
    mouseButtonListeners.push_back(listener);
}

void Window::addScrollListener(MouseScrollListener* listener) {
    scrollListeners.push_back(listener);
}

void Window::removeKeyListener(KeyPressListener* listener) {
    auto it = std::find(keyPressListeners.begin(), keyPressListeners.end(), listener);
    keyPressListeners.erase(it);
}

void Window::removeMouseButtonListener(MouseButtonListener* listener) {
    auto it = std::find(mouseButtonListeners.begin(), mouseButtonListeners.end(), listener);
    mouseButtonListeners.erase(it);
}

void Window::removeScrollListener(MouseScrollListener* listener) {
    auto it = std::find(scrollListeners.begin(), scrollListeners.end(), listener);
    scrollListeners.erase(it);
}

void Window::onKeyPress(KeyCode key, ActionState state) {
    for (int i = keyPressListeners.size() - 1; i >= 0; i--) {
        keyPressListeners[i]->onKeyPressed(key, state);
    }
}

void Window::onMouseButtonClick(MouseButton button, ActionState state) {
    for (int i = mouseButtonListeners.size() - 1; i >= 0; i--) {
        mouseButtonListeners[i]->onMouseButtonClicked(button, state);
    }
}

void Window::onScroll(float amount) {
    for (int i = scrollListeners.size() - 1; i >= 0; i--) {
        scrollListeners[i]->onMouseScroll(amount);
    }
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

void Window::getMouseDelta(double& dx, double& dy) {
    dx = this->dx;
    dy = this->dy;
}

bool Window::isKeyPressed(int KeyCode) {
    return glfwGetKey(window, KeyCode) == GLFW_PRESS;
}

void Window::pollEvents() {
    glfwPollEvents();

    if (activeWindow == nullptr) return;

    double x, y;
    glfwGetCursorPos(this->window, &x, &y);

    dx = x - lastX;
    dy = lastY - y;

    lastX = x;
    lastY = y;
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
    if (activeWindow == nullptr) return;
    activeWindow->getWindowSize(width, height);
}

void Window::terminate() {
    glfwTerminate();
}

Window::~Window() {
    if (activeWindow == this) {
        activeWindow = nullptr;
    }
}
