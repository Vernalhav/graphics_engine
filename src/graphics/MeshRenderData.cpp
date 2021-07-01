#include "MeshRenderData.h"

MeshRenderData::MeshRenderData() : vaoId(-1), vboId(-1), eboId(-1), materialPath(""), texture() { }
MeshRenderData::MeshRenderData(const std::string& texturePath)
	: vaoId(-1), vboId(-1), eboId(-1), materialPath(""), texture(texturePath) { }