#include "Renderer.h"

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

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), vertices.data(), GL_STATIC_DRAW);
}

void Renderer::drawObject(SceneObject* object) {
	shader.use();
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	_drawObject(object, Transform());
}

void Renderer::_drawObject(const SceneObject* object, Transform globalTransform) {
	
	globalTransform += object->getTransform();

	auto objectPrimitive = object->getObjectPrimitive();
	for (auto& subprimitive : objectPrimitive) {
		shader.setTransform(globalTransform);
		glDrawArrays(subprimitive.primitive, subprimitive.offset, subprimitive.getVertexCount());
	}

	for (auto& child : object->getChildren()) {
		_drawObject(child, globalTransform);
	}
}

Renderer::Renderer(Shader s) : shader(s), VBO(0) {
	glGenVertexArrays(1, &VAO);
}
