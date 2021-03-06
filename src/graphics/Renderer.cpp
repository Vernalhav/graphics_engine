#include "Renderer.h"

#include <iostream>

enum class PolygonMode {
	Fill, Wireframe
};


void Renderer::uploadMesh(RenderData* mesh) {
	if (mesh->vaoId > 0) return;

	const int VERTEX_ELEMENT_COUNT = 8;	// Number of 4-byte elements in a vertex

	// FIXME: use single VAO?
	glGenVertexArrays(1, (GLuint*)&(mesh->vaoId));
	glGenBuffers(1, (GLuint*)&(mesh->vboId));

	// Stores all vertex attributes in a contiguous array
	std::vector<float> vboData(VERTEX_ELEMENT_COUNT * mesh->vertices.size());

	for (unsigned int i = 0; i < mesh->vertices.size(); i++) {
		int baseIdx = VERTEX_ELEMENT_COUNT * i;

		// FIXME: quick and dirty implementation (should ideally just be sending mesh->vertices to VBO)
		vboData[baseIdx + 0] = mesh->vertices[i].position[0];
		vboData[baseIdx + 1] = mesh->vertices[i].position[1];
		vboData[baseIdx + 2] = mesh->vertices[i].position[2];
		vboData[baseIdx + 3] = mesh->vertices[i].textureCoords[0];
		vboData[baseIdx + 4] = mesh->vertices[i].textureCoords[1];
		vboData[baseIdx + 5] = mesh->vertices[i].normal[0];
		vboData[baseIdx + 6] = mesh->vertices[i].normal[1];
		vboData[baseIdx + 7] = mesh->vertices[i].normal[2];
	}

	glBindVertexArray(mesh->vaoId);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vboId);
	glBufferData(GL_ARRAY_BUFFER, vboData.size() * sizeof(float), vboData.data(), GL_STATIC_DRAW);

	shader->enableAttributes();
	shader->setAttributeLayout();

	for (auto& elem : mesh->subMeshes) {
		SubMesh& currentMesh = elem.second;

		glGenBuffers(1, (GLuint*)&currentMesh.eboId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, currentMesh.eboId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, currentMesh.indices.size() * sizeof(int), currentMesh.indices.data(), GL_STATIC_DRAW);
	}
}

void Renderer::setViewPosition(const glm::vec3& position) {
	shader->setViewPosition(position);
}

void Renderer::drawObject(RenderData* object, const glm::mat4& model, const glm::mat4& viewProjection) {
	glBindVertexArray(object->vaoId);
	glBindBuffer(GL_ARRAY_BUFFER, object->vboId);
	shader->setMVPMatrix(model, viewProjection);

	for (auto& elem : object->subMeshes) {
		SubMesh& currentMesh = elem.second;
		shader->setMaterial(currentMesh.material);

		if (currentMesh.material.texture != nullptr) {
			currentMesh.material.texture->bind(Shader::MAIN_TEXTURE_SLOT);
		}

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, currentMesh.eboId);
		glDrawElements(GL_TRIANGLES, currentMesh.indices.size(), GL_UNSIGNED_INT, nullptr);
	}
}

void Renderer::toggleDrawMode() {
	polygonMode = (polygonMode == PolygonMode::Fill) ? PolygonMode::Wireframe : PolygonMode::Fill;
	GLenum illumMode = (polygonMode == PolygonMode::Fill) ? GL_FILL : GL_LINE;
	glPolygonMode(GL_FRONT_AND_BACK, illumMode);
}

Shader* Renderer::getShader() {
	return shader;
}

Renderer::Renderer(Shader* s) : shader(s), polygonMode(PolygonMode::Fill), VAO(0) {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

Renderer::~Renderer() {
	delete shader;
}
