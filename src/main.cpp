#include <GL/glew.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "Primitive.h"
#include "SceneObject.h"
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

    return window;
}


GLuint setupShaders(std::string vertex_code, std::string fragment_code, std::vector<Vector3> vertices) {

    if (vertices.size() == 0) {
        printf("Vertices array has size 0. Aborting shader compilation.");
        return -1;
    }

    GLuint program = glCreateProgram();
    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

    const char* vertex_code_str = vertex_code.c_str();
    const char* frag_code_str = fragment_code.c_str();

    glShaderSource(vertex, 1, &vertex_code_str, NULL);
    glShaderSource(fragment, 1, &frag_code_str, NULL);

    glCompileShader(vertex);

    GLint isCompiled = 0;
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE) {

        int infoLength = 512;
        glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &infoLength);

        char* info = (char*)malloc(infoLength * sizeof(char));
        glGetShaderInfoLog(vertex, infoLength, NULL, info);

        printf("Erro de compilacao no Vertex Shader.\n");
        printf("--> %s\n", info);

        free(info);
    }

    glCompileShader(fragment);

    isCompiled = 0;
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE) {

        GLint infoLength = 512;
        glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &infoLength);

        char* info = (char*)malloc(infoLength * sizeof(char));
        glGetShaderInfoLog(fragment, infoLength, NULL, info);

        printf("Erro de compilacao no Fragment Shader.\n");
        printf("--> %s\n", info);

        free(info);
    }

    glAttachShader(program, vertex);
    glAttachShader(program, fragment);

    glLinkProgram(program);
    glUseProgram(program);

    GLuint vbo, vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), vertices.data(), GL_DYNAMIC_DRAW);

    GLint loc = glGetAttribLocation(program, "position");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), nullptr); // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glVertexAttribPointer.xhtml

    return program;
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


std::vector<Primitive> getPropeller(float width = 0.1, float length = 1, int nPropellers = 3) {
    
    std::vector<Primitive> prop;

    float stepAngle = 2 * PI / nPropellers;
    
    for (int i = 0; i < nPropellers; i++) {
        prop.push_back(Primitive(
            getRectangle(width, length, i * stepAngle),
            GL_TRIANGLE_FAN,
            255, 255, 255
        ));
    }

    return prop;
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
        "attribute vec2 position;\n"
        "uniform vec2 translation;\n"
        "uniform float rotation;\n"
        "uniform float scale;\n"
        "void main()\n"
        "{\n"
        "   mat3 translation_mat = mat3( vec3(1, 0, 0), vec3(0, 1, 0), vec3(translation, 0) );\n"
        "   mat3 rotation_mat = mat3( vec3(cos(rotation), sin(rotation), 0), vec3(-sin(rotation), cos(rotation), 0), vec3(0, 0, 1) );\n"
        "   mat3 scale_mat = mat3( vec3(scale, 0, 0), vec3(0, scale, 0), vec3(0, 0, 1) );\n"
        "   gl_Position = vec4(translation_mat * scale_mat * rotation_mat * vec3(position, 1.0), 1.0);\n"
        "}\n";

    std::string fragment_code =
        "#version 150\n"
        "uniform vec4 color;\n"
        "void main()\n"
        "{\n"
        "    gl_FragColor = color;\n"
        "}\n";

    std::vector<Primitive> primitives = getPropeller(0.05f, 0.5f, 3);

    std::vector<Vector3> vertices;
    for (Primitive p : primitives) {
        vertices.insert(vertices.end(), p.vertices.begin(), p.vertices.end());
    }

    GLint program = setupShaders(vertex_code, fragment_code, vertices);
    GLint rotationLoc = glGetUniformLocation(program, "rotation");
    GLint positionLoc = glGetUniformLocation(program, "position");
    GLint translationLoc = glGetUniformLocation(program, "translation");
    GLint scaleLoc = glGetUniformLocation(program, "scale");
    GLint colorLoc = glGetUniformLocation(program, "color");

    glfwShowWindow(window);

    while (!glfwWindowShouldClose(window))
    {

        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.0, 0.0, 0.0, 1.0);

        int offset = 0;
        for (Primitive& p : primitives) {
            p.rotation += 0.001f;
            //processInput(p.rotation, p.scale, p.translation);

            glUniform4f(colorLoc, p.color[0], p.color[1], p.color[2], p.color[3]);
            glUniform1f(rotationLoc, p.rotation);
            glUniform1f(scaleLoc, p.scale);
            glUniform2f(translationLoc, p.translation[0], p.translation[1]);

            glDrawArrays(p.primitive, offset, p.vertices.size());
            offset += p.vertices.size();
        }

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}
