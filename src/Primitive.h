#pragma once

#include <GL/glew.h>
#include <vector>
#include "vectors.h"


struct Primitive {
    std::vector<Vector3> vertices;
    Vector4 color;
    GLenum primitive;

    int offset = -1; // Offset of the vertices of this Primitive inside the VBO

    Primitive() : vertices(), primitive(GL_TRIANGLE_FAN), color() { }

    Primitive(std::vector<Vector3>&& verts, GLenum prim, Vector3 color)
        : vertices(verts), primitive(prim), color({ color.x / 255.0f, color.y / 255.0f, color.z / 255.0f, 1.0f }) { }

    Primitive(std::vector<Vector3>& verts, GLenum prim, Vector3 color)
        : vertices(verts), primitive(prim), color({ color.x / 255.0f, color.y / 255.0f, color.z / 255.0f, 1.0f }) { }

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

    int getSingleVertexSize() {
        return sizeof(vertices[0]);
    }
};
