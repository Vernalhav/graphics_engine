#include "Vertex.h"

Vertex::Vertex() : position(0), textureCoords(0), normal(0), color(0) { }

Vertex::Vertex(const glm::vec3& position, const glm::vec2& uvCoords)
	: position(position), textureCoords(uvCoords), normal(0), color(0) { }

Vertex::Vertex(const glm::vec3& position, const glm::vec4& color)
	: position(position), color(color), normal(0), textureCoords(0) { }

Vertex::Vertex(const glm::vec3& position, const glm::vec2& uvCoords, const glm::vec3& normal)
	: position(position), textureCoords(uvCoords), normal(normal), color(0) { }

Vertex::Vertex(const glm::vec3& position, const glm::vec4& color, const glm::vec3& normal)
	: position(position), color(color), normal(normal), textureCoords(0) { }
