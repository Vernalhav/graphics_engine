#include <iostream>

#include "Renderer.h"


void Renderer::uploadMesh(MeshRenderData* mesh) {
	if (mesh->vaoId > 0) return;

	mesh->vaoId = VAO;
	glGenBuffers(1, (GLuint*)&(mesh->vboId));
	glGenBuffers(1, (GLuint*)&(mesh->eboId));

	// Stores all vertex attributes in a contiguous array
	std::vector<float> vboData(5 * mesh->vertices.size());

	for (unsigned int i = 0; i < mesh->vertices.size(); i++) {
		int baseIdx = 5 * i;

		// FIXME: quick and dirty implementation (should ideally just be sending mesh->vertices to VBO)
		vboData[baseIdx + 0] = mesh->vertices[i].position[0];
		vboData[baseIdx + 1] = mesh->vertices[i].position[1];
		vboData[baseIdx + 2] = mesh->vertices[i].position[2];
		vboData[baseIdx + 3] = mesh->vertices[i].textureCoords[0];
		vboData[baseIdx + 4] = mesh->vertices[i].textureCoords[1];
	}

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vboId);
	glBufferData(GL_ARRAY_BUFFER, vboData.size() * sizeof(float), vboData.data(), GL_STATIC_DRAW);

	shader.enableAttributes();
	shader.setAttributeLayout();

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
	shader.enableAttributes();
}

void Renderer::drawObject(MeshRenderData* object, const glm::mat4& transform) {
	glBindBuffer(GL_ARRAY_BUFFER, object->vboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object->eboId);

	object->texture.bind(Shader::MAIN_TEXTURE_SLOT);

	shader.setTransform(transform);

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
