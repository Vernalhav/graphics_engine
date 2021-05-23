#pragma once

#include <GL/glew.h>
#include <vector>
#include "vectors.h"


struct Primitive {
    std::vector<Vector3> vertices;
    Vector4 color;
    GLenum primitive;

    float rotation = 0;
    float scale = 1;
    float translation[2] = { 0, 0 };

    int offset = -1; // Offset of the vertices of this Primitive inside the VBO

    Primitive() : vertices(), primitive(GL_TRIANGLE_FAN), color() { }

    Primitive(std::vector<Vector3>&& verts, GLenum prim, int r, int g, int b)
        : vertices(verts), primitive(prim), color({ r / 255.0f, g / 255.0f, b / 255.0f, 1.0f }) { }

    Primitive(std::vector<Vector3>& verts, GLenum prim, int r, int g, int b)
        : vertices(verts), primitive(prim), color({ r / 255.0f, g / 255.0f, b / 255.0f, 1.0f }) { }

    /// <summary>
    /// Returns amount of bytes occupied by the
    /// vertices of this Primitive.
    /// </summary>
    /// <returns></returns>
    int getSizeOfVertices() {
        return vertices.size() * sizeof(vertices[0]);
    }

    int getVertexCount() {
        return vertices.size();
    }
};
