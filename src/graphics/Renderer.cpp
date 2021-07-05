#include <iostream>

#include "Renderer.h"

enum class PolygonMode {
	Fill, Wireframe
};


void Renderer::uploadMesh(RenderData* mesh) {
	if (mesh->vaoId > 0) return;

	// FIXME: use single VAO?
	glGenVertexArrays(1, (GLuint*)&(mesh->vaoId));
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

	glBindVertexArray(mesh->vaoId);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vboId);
	glBufferData(GL_ARRAY_BUFFER, vboData.size() * sizeof(float), vboData.data(), GL_STATIC_DRAW);

	shader.enableAttributes();
	shader.setAttributeLayout();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->eboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->indices.size() * sizeof(int), mesh->indices.data(), GL_STATIC_DRAW);
}

void Renderer::drawObject(RenderData* object, const glm::mat4& mvp) {
	glBindVertexArray(object->vaoId);
	glBindBuffer(GL_ARRAY_BUFFER, object->vboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object->eboId);

	object->texture.bind(Shader::MAIN_TEXTURE_SLOT);

	shader.setMVPMatrix(mvp);

	glDrawElements(GL_TRIANGLES, object->indices.size(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::toggleDrawMode() {
	GLenum mode = (polygonMode == PolygonMode::Fill) ? GL_FILL : GL_LINE;
	glPolygonMode(GL_FRONT_AND_BACK, mode);
	polygonMode = (polygonMode == PolygonMode::Fill) ? PolygonMode::Wireframe : PolygonMode::Fill;
}

Renderer::Renderer(Shader s) : shader(s), polygonMode(PolygonMode::Fill), VAO(0) {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

Renderer::~Renderer() {
}
