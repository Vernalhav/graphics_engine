#include "Renderer.h"
#include <iostream>

void Renderer::uploadObjects(std::vector<SceneObject*> objects) {

	std::vector<Vector3> vertices;

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

	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	GLsizeiptr bufferSize = vertices.size() * sizeof(vertices[0]);
	glBufferData(GL_ARRAY_BUFFER, bufferSize, vertices.data(), GL_STATIC_DRAW);

	shader.setPositionAttributeLayout();
	shader.enableAttrib("position");
}

void Renderer::drawObject(SceneObject* object) {
	shader.use();
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	_drawObject(object, Transform());
}

void Renderer::_drawObject(const SceneObject* object, Transform globalTransform) {
	
	globalTransform += object->getTransform();
	shader.setTransform(globalTransform);
	//std::cout << globalTransform << std::endl;

	auto objectPrimitive = object->getObjectPrimitive();

	for (auto& subprimitive : objectPrimitive) {
		shader.setFloat4("color", subprimitive.color);
		glDrawArrays(subprimitive.primitive, subprimitive.offset, subprimitive.getVertexCount());
	}

	for (auto& child : object->getChildren()) {
		_drawObject(child, globalTransform);
	}
}

Renderer::Renderer(Shader s) : shader(s), VBO(0) {
	glGenVertexArrays(1, &VAO);
}
