#pragma once

#include <vector>

#include "Primitive.h"
#include "SceneObject.h"

/// <summary>
/// Uploads the scene objects' vertex data to a Vertex Buffer Object
/// and writes to each Primitive's offset member and returns the name
/// of the created VBO.
/// </summary>
/// <param name="objects">Top-level objects in the scene</param>
GLuint uploadObjects(std::vector<SceneObject*> objects) {

	std::vector<std::pair<float, float>> vertices;

	int offset = 0;
	for (auto object : objects) {
		std::vector<Primitive>&& curPrimitives = object->getObjectPrimitives();

		for (Primitive& primitive : curPrimitives) {
			primitive.offset = offset;
			int size = primitive.getSizeOfVertices();

			vertices.insert(vertices.end(), primitive.vertices.begin(), primitive.vertices.end());

			offset += size;
		}
	}

	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), vertices.data(), GL_STATIC_DRAW);

	return VBO;
}