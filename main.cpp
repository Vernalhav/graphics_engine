/* para linux, instalar os pacotes libglfw3-dev mesa-common-dev libglew-dev */
/* para compilar no linux: gcc main.c -lglfw -lGL -lGLEW -lm */

/* para windows, instalar bibliotecas compiladas do glfw3 e glew no ambiente mingw */
/* para compilar no windows: gcc main.c -lglfw3dll -lglew32 -lopengl32 */


#include <GL/glew.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h> /* verifique no seu SO onde fica o glfw3.h */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "Primitive.h"
#include "SceneObject.h"


#define PI 3.14159265359
#define DEG2RAD (PI / 180)


GLFWwindow* initGLFW() {
    // inicicializando o sistema de\ janelas
    glfwInit();

    // deixando a janela invisivel, por enquanto
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

    // criando uma janela
    GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL Window", nullptr, nullptr);

    // tornando a janela como principal 
    glfwMakeContextCurrent(window);
    return window;
}


GLuint setupShaders(std::string vertex_code, std::string fragment_code, std::vector<std::pair<float, float>> vertices) {

    if (vertices.size() == 0) {
        printf("Vertices array has size 0. Aborting shader compilation.");
        return -1;
    }

    // inicializando Glew (para lidar com funcoes OpenGL)
    GLint GlewInitResult = glewInit();
    printf("GlewStatus: %s", glewGetErrorString(GlewInitResult));

    // Requisitando slot para a GPU para nossos programas Vertex e Fragment Shaders
    GLuint program = glCreateProgram();
    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

    const char* vertex_code_str = vertex_code.c_str();
    const char* frag_code_str = fragment_code.c_str();

    // Associando nosso c�digo-fonte GLSL aos slots solicitados
    glShaderSource(vertex, 1, &vertex_code_str, NULL);
    glShaderSource(fragment, 1, &frag_code_str, NULL);

    // Compilando o Vertex Shader e verificando erros
    glCompileShader(vertex);

    GLint isCompiled = 0;
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE) {

        //descobrindo o tamanho do log de erro
        int infoLength = 512;
        glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &infoLength);

        //recuperando o log de erro e imprimindo na tela
        char* info = (char*)malloc(infoLength * sizeof(char));
        glGetShaderInfoLog(vertex, infoLength, NULL, info);

        printf("Erro de compilacao no Vertex Shader.\n");
        printf("--> %s\n", info);

        free(info);
    }

    // Compilando o Fragment Shader e verificando erros
    glCompileShader(fragment);

    isCompiled = 0;
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE) {

        //descobrindo o tamanho do log de erro
        GLint infoLength = 512;
        glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &infoLength);

        char* info = (char*)malloc(infoLength * sizeof(char));
        //recuperando o log de erro e imprimindo na tela
        glGetShaderInfoLog(fragment, infoLength, NULL, info);

        printf("Erro de compilacao no Fragment Shader.\n");
        printf("--> %s\n", info);

        free(info);
    }

    // Associando os programas compilado ao programa principal
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);

    // Linkagem do programa e definindo como default
    glLinkProgram(program);
    glUseProgram(program);

    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);

    // Abaixo, n�s enviamos todo o conte�do da vari�vel vertices.
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), vertices.data(), GL_DYNAMIC_DRAW);

    // Associando vari�veis do programa GLSL (Vertex Shaders) com nossos dados
    GLint loc = glGetAttribLocation(program, "position");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), nullptr); // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glVertexAttribPointer.xhtml

    return program;
}


std::vector<std::pair<float, float>> getPolygon(int n, float radius = 1.0, float rotation = 0.0, std::pair<float, float> offset = { 0, 0 }) {
    std::vector<std::pair<float, float>> polygon(n);

    float angleStep = 2 * PI / n;
    for (int i = 0; i < n; i++) {
        polygon[i].first = radius * cos(angleStep * i + rotation);
        polygon[i].second = radius * sin(angleStep * i + rotation);
    }

    return polygon;
}


std::vector<std::pair<float, float>> getRectangle(float width, float length, float rotation) {
    std::vector<std::pair<float, float>> rectangle(4);

    rectangle[0] = { 0, width / 2 };
    rectangle[1] = { 0, - width / 2 };
    rectangle[2] = { length, - width / 2 };
    rectangle[3] = { length, width / 2 };

    for (auto& vertex : rectangle) {
        float x = vertex.first, y = vertex.second;
        vertex.first = cos(rotation) * x - sin(rotation) * y;
        vertex.second = sin(rotation) * x + cos(rotation) * y;
    }

    return rectangle;
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

    float rotationPerFrame = 0.005;
    float scalePerFrame = 0.005;
    float TranslationPerFrame = 0.005;

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

    double stepAngle = 2 * PI / nPropellers;
    
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

    std::string vertex_code =
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
        "uniform vec4 color;\n"
        "void main()\n"
        "{\n"
        "    gl_FragColor = color;\n"
        "}\n";

    std::vector<Primitive> primitives = getPropeller(0.05, 0.5, 3);

    std::vector<std::pair<float, float>> vertices;
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
            p.rotation += 0.001;
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
