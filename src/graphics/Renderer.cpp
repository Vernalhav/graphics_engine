#include <iostream>

#include "Renderer.h"


void Renderer::uploadMesh(MeshRenderData* mesh) {
	if (mesh->vaoId > 0) return;

	mesh->vaoId = VAO;
	glGenBuffers(1, (GLuint*)&(mesh->vboId));
	glGenBuffers(1, (GLuint*)&(mesh->eboId));

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vboId);
	glBufferData(GL_ARRAY_BUFFER, mesh->vertices.size() * sizeof(float), mesh->vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->eboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->indices.size() * sizeof(int), mesh->indices.data(), GL_STATIC_DRAW);
}

void Renderer::uploadObjects(std::vector<SceneObject*> objects) {

	std::vector<glm::vec3> vertices;

	int offset = 0;
	for (auto object : objects) {
		std::vector<Primitive*> curPrimitives = object->getObjectPrimitives();

		for (Primitive* primitive : curPrimitives) {
			primitive->offset = offset;
			int size = primitive->getSizeOfVertices();

			vertices.insert(vertices.end(), primitive->vertices.begin(), primitive->vertices.end());
			offset += size;
		}
	}

	GLuint VBO;
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	GLsizeiptr bufferSize = vertices.size() * sizeof(vertices[0]);
	glBufferData(GL_ARRAY_BUFFER, bufferSize, vertices.data(), GL_STATIC_DRAW);

	shader.setAttributeLayout();
}

void Renderer::drawObject(MeshRenderData* object) {
	glBindBuffer(GL_VERTEX_ARRAY, object->vboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object->eboId);

	glDrawElements(GL_TRIANGLES, object->indices.size(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::_drawObject(const SceneObject* object, glm::mat4 globalTransform) {
	
	globalTransform = globalTransform * object->transform.getTransformMatrix();
	shader.setTransform(globalTransform);

	auto objectPrimitive = object->getObjectPrimitive();

	for (auto& subprimitive : objectPrimitive) {
		shader.setFloat4("color", subprimitive.color);
		glDrawArrays(subprimitive.primitive, subprimitive.offset / subprimitive.getSingleVertexSize(), subprimitive.getVertexCount());
	}

	for (auto& child : object->getChildren()) {
		_drawObject(child, globalTransform);
	}
}

Renderer::Renderer(Shader s) : shader(s) {
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
}
