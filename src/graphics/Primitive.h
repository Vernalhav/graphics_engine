#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <vector>

struct Primitive {
    std::vector<glm::vec3> vertices;
    glm::vec4 color;
    GLenum primitive;

    int offset = -1; // Offset of the vertices of this Primitive inside the VBO

    Primitive() : vertices(), primitive(GL_TRIANGLE_FAN), color() { }

    Primitive(std::vector<glm::vec3>&& verts, GLenum prim, glm::vec3 color)
        : vertices(verts), primitive(prim), color(color/255.0f, 1.0f) { }

    Primitive(std::vector<glm::vec3>& verts, GLenum prim, glm::vec3 color)
        : vertices(verts), primitive(prim), color(color/255.0f, 1.0f) { }

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
