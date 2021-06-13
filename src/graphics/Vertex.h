#pragma once
#include <glm/glm.hpp>

struct Vertex {
	glm::vec3 position;
	glm::vec2 textureCoords;
	glm::vec3 normal;
	glm::vec4 color;

	Vertex();

	/// <summary>
	/// Constructs a vertex with a given texture
	/// coordinate instead of a solid colour.
	/// </summary>
	Vertex(const glm::vec3& position, const glm::vec2& uvCoords);
	Vertex(const glm::vec3& position, const glm::vec2& uvCoords, const glm::vec3& normal);
	
	/// <summary>
	/// Constructs a vertex with a given color
	/// instead of texture coordinates
	/// </summary>
	Vertex(const glm::vec3& position, const glm::vec4& color);
	Vertex(const glm::vec3& position, const glm::vec4& color, const glm::vec3& normal);
	
	~Vertex() = default;

};