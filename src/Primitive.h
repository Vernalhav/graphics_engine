#pragma once

#include <GL/glew.h>
#include <vector>

struct Vector3 {
    float x, y, z;

    Vector3(float x, float y, float z) : x(x), y(y), z(z) { }
    Vector3(float x, float y) : x(x), y(y), z(1) { }
    Vector3(float x) : x(x), y(0), z(1) { }
    Vector3() : x(0), y(0), z(1) { }
};


struct Primitive {
    std::vector<Vector3> vertices;
    float color[4];
    GLenum primitive;

    float rotation = 0;
    float scale = 1;
    float translation[2] = { 0, 0 };

    int offset = -1; // Offset of the vertices of this Primitive inside the VBO

    Primitive() : vertices(), primitive(GL_TRIANGLE_FAN) {
        color[0] = 1;
        color[1] = 1;
        color[2] = 1;
        color[3] = 1;
    }

    Primitive(std::vector<Vector3>&& verts, GLenum prim, int r, int g, int b) : vertices(verts), primitive(prim) {
        color[0] = r / 255.0f;
        color[1] = g / 255.0f;
        color[2] = b / 255.0f;
        color[3] = 1.0f;
    }

    Primitive(std::vector<Vector3>& verts, GLenum prim, int r, int g, int b) : vertices(verts), primitive(prim) {
        color[0] = r / 255.0f;
        color[1] = g / 255.0f;
        color[2] = b / 255.0f;
        color[3] = 1.0f;
    }

    /// <summary>
    /// Returns amount of bytes occupied by the
    /// vertices of this Primitive.
    /// </summary>
    /// <returns></returns>
    int getSizeOfVertices() {
        return vertices.size() * sizeof(vertices[0]);
    }
};
