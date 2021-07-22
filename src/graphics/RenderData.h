#pragma once

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <filesystem>

#include "Vertex.h"
#include "Texture.h"
#include "Material.h"

namespace fs = std::filesystem;


struct SubMesh {
	Material material;
	std::vector<int> indices;

	SubMesh() : material(), eboId(-1) { };
	SubMesh(Material m) : material(m), eboId(-1) { };
	~SubMesh() { glDeleteBuffers(1, (const GLuint *)&eboId); };

private:
	friend class Renderer;
	int eboId;
};

struct RenderData {
	std::vector<Vertex> vertices;	// Unique vertices and their attributes
	
	std::map<std::string, SubMesh> subMeshes;

	RenderData(const fs::path& filePath);
	~RenderData();

private:
	friend class Renderer;
	int vaoId;	// Id of the Mesh's OpenGL vertex array object
	int vboId;	// Id of the Mesh's OpenGL vertex buffer object
};