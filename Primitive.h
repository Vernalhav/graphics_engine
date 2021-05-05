#pragma once

#include <GL/glew.h>


struct Primitive {
    std::vector<std::pair<float, float>> vertices;
    float color[4];
    GLenum primitive;

    float rotation = 0;
    float scale = 1;
    float translation[2] = { 0, 0 };

    Primitive() : vertices(), primitive(GL_TRIANGLE_FAN) {
        color[0] = 1;
        color[1] = 1;
        color[2] = 1;
        color[3] = 1;
    }

    Primitive(std::vector<std::pair<float, float>>&& verts, GLenum prim, int r, int g, int b) : vertices(verts), primitive(prim) {
        color[0] = r / 255.0;
        color[1] = g / 255.0;
        color[2] = b / 255.0;
        color[3] = 1.0;
    }

    Primitive(std::vector<std::pair<float, float>>& verts, GLenum prim, int r, int g, int b) : vertices(verts), primitive(prim) {
        color[0] = r / 255.0;
        color[1] = g / 255.0;
        color[2] = b / 255.0;
        color[3] = 1.0;
    }
};
