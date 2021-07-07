#include "RenderData.h"

#include <fstream>
#include <iostream>
#include <unordered_map>

#include "../misc/utils.h"


/// <summary>
/// Using an unnamed namespace to declare
/// "private" funcions and structs that are
/// only visible in this .cpp file
/// </summary>
namespace {

	/// <summary>
	/// Position, normal and texture coordinate index
	/// of a face vertex read from an .obj file.
	/// Indices are 0-based.
	/// </summary>
	struct VertexIndexInfo {
		int positionIdx;
		int textureCoordsIdx;
		int normalIdx;
		std::string textureName;

		VertexIndexInfo() : positionIdx(-1), textureCoordsIdx(-1), normalIdx(-1) { }

		VertexIndexInfo(int posIdx, int uvCoordsIdx, int normalIdx, const std::string& textureName)
			: positionIdx(posIdx), textureCoordsIdx(uvCoordsIdx), normalIdx(normalIdx), textureName(textureName) { };

		bool operator==(const VertexIndexInfo& other) const {
			return positionIdx == other.positionIdx &&
				textureCoordsIdx == other.textureCoordsIdx &&
				normalIdx == other.normalIdx &&
				textureName == other.textureName;
		}
	};

	// Aliasing type std::vector<VertexIndexInfo> to refer to a mesh Face
	using Face = std::vector<VertexIndexInfo>;

	Face parseFace(const std::vector<std::string>& lineTokens) {
		Face face;

		for (size_t i = 1; i < lineTokens.size(); i++) {
			std::vector<std::string> vertexIndices = utils::split(lineTokens[i], '/', false);
			int nAttributes = vertexIndices.size();

			VertexIndexInfo currentVertex;
			if (nAttributes >= 1 && !vertexIndices[0].empty())
				currentVertex.positionIdx = std::stoi(vertexIndices[0]) - 1;

			if (nAttributes >= 2 && !vertexIndices[1].empty())
				currentVertex.textureCoordsIdx = std::stoi(vertexIndices[1]) - 1;

			if (nAttributes >= 3 && !vertexIndices[2].empty())
				currentVertex.normalIdx = std::stoi(vertexIndices[2]) - 1;

			face.push_back(currentVertex);
		}

		return face;
	}

	glm::vec3 parseVertexPosition(const std::vector<std::string>& lineTokens) {
		if (lineTokens.size() != 4) {
			std::cout << "ERROR: parseVertex: could not parse vertex position" << std::endl;
			return glm::vec3();
		}

		float x = stof(lineTokens[1]);
		float y = stof(lineTokens[2]);
		float z = stof(lineTokens[3]);

		return glm::vec3(x, y, z);
	}

	glm::vec2 parseTextureCoords(const std::vector<std::string>& lineTokens) {
		if (lineTokens.size() != 3) {
			std::cout << "ERROR: parseTextureCoords: could not parse texture coordinate" << std::endl;
			return glm::vec2();
		}

		float u = stof(lineTokens[1]);
		float v = stof(lineTokens[2]);

		return glm::vec2(u, v);
	}

	glm::vec3 parseNormal(const std::vector<std::string>& lineTokens) {
		if (lineTokens.size() != 4) {
			std::cout << "ERROR: parseVertex: could not parse normal" << std::endl;
			return glm::vec3();
		}

		float x = stof(lineTokens[1]);
		float y = stof(lineTokens[2]);
		float z = stof(lineTokens[3]);

		return glm::vec3(x, y, z);
	}

	std::map<std::string, Material> loadMTL(const fs::path& filePath) {

		std::ifstream mtlFile;
		mtlFile.open(filePath);

		std::map<std::string, Material> textures;

		if (mtlFile.is_open()) {

			int lineNum = 1;
			std::string textureName;
			glm::vec3 textureColor;
			fs::path texturePath;

			for (std::string line; std::getline(mtlFile, line); lineNum++) {
				std::vector<std::string> lineTokens = utils::split(line);

				if (lineTokens.size() == 0 || lineTokens[0][0] == '#') continue;

				if (lineTokens[0] == "newmtl") {
					if (!textureName.empty()) {
						std::cout << "Loading texture " << textureName << " (" << texturePath.generic_string() << ")... ";
						textures[textureName] = Material(textureName, textureColor, texturePath);
						std::cout << "done!" << std::endl;
						texturePath = "";
					}
					
					textureName = lineTokens[1];
				}
				if (lineTokens[0] == "Kd") textureColor = { std::stod(lineTokens[1]),
															std::stod(lineTokens[2]),
															std::stod(lineTokens[3]) };
				
				if (lineTokens[0] == "map_Kd" || lineTokens[0] == "map_d") {
					fs::path basePath = filePath;
					texturePath = basePath.replace_filename(lineTokens[1]);
				}
			}

			if (!textureName.empty()) {
				std::cout << "Loading texture " << textureName << " (" << texturePath.generic_string() << ")... ";
				textures[textureName] = Material(textureName, textureColor, texturePath);
				std::cout << "done!" << std::endl;
				texturePath = "";
			}

			mtlFile.close();
			return textures;
		}
		else {
			std::cout << "ERROR: loadMTL: could not open mtl file " << filePath << std::endl;
			return std::map<std::string, Material>();
		}
	}
}

RenderData::RenderData(const fs::path& filePath)
	: vaoId(-1), vboId(-1) {

	std::ifstream objFile;
	objFile.open(filePath);

	if (objFile.is_open()) {
		std::cout << std::endl << "Loading object file " << filePath << "..." << std::endl;

		std::vector<glm::vec3> positions;
		std::vector<glm::vec2> textureCoords;
		std::vector<glm::vec3> normals;
		std::map<std::string, std::vector<Face>> faces;

		std::map<std::string, Material> materials;

		std::string currentMaterial;
		int lineNum = 1;
		for (std::string line; std::getline(objFile, line); lineNum++) {
			std::vector<std::string> lineTokens = utils::split(line);
			if (lineTokens.size() == 0 || lineTokens[0][0] == '#') continue;

			if (lineTokens[0] == "mtllib") {
				fs::path pathToObj = filePath;
				fs::path mtlLibPath = pathToObj.replace_filename(lineTokens[1]);

				std::cout << "Loading material lib " << mtlLibPath.generic_string() << "... " << std::endl;
				materials = loadMTL(mtlLibPath);
				std::cout << "Done loading " << mtlLibPath.generic_string() << std::endl;
			}

			if (lineTokens[0] == "v") positions.push_back(parseVertexPosition(lineTokens));
			if (lineTokens[0] == "vn") normals.push_back(parseNormal(lineTokens));
			if (lineTokens[0] == "vt") textureCoords.push_back(parseTextureCoords(lineTokens));
			if (lineTokens[0] == "usemtl") currentMaterial = lineTokens[1];

			if (lineTokens[0] == "f") {
				faces[currentMaterial].push_back(parseFace(lineTokens));
			}
		}

		objFile.close();

		// As an optimization, we'll try to reuse as many vertices as possible by
		// indexing; therefore we must know which vertices have already been used.

		// Quick and dirty hash function for VertexIndexInfo to use with unordered_map
		auto hash = [](const VertexIndexInfo& a) {
			return (a.normalIdx << 16) ^ (a.textureCoordsIdx << 8) ^ (a.positionIdx)
				+ std::hash<std::string>{}(a.textureName);
		};

		std::cout << "Processing vertices from " << filePath << "..." << std::endl;

		// Mapping between unique vertex attribute indices and the vertex index in the vertex array
		std::unordered_map<VertexIndexInfo, int, decltype(hash)> vertexIndexInBuffer(2048, hash);

		for (auto& _materialFaces : faces) {
			const std::string& materialName = _materialFaces.first;
			const std::vector<Face>& materialFaces = _materialFaces.second;

			this->subMeshes[materialName].material = materials[materialName];

			for (const Face& face : materialFaces) {
				for (const VertexIndexInfo& vertex : face) {
					if (vertexIndexInBuffer.count(vertex)) {
						this->subMeshes[materialName].indices.push_back(vertexIndexInBuffer[vertex]);
					}
					else {
						int newVertexIndex = this->vertices.size();

						Vertex newVertex;
						if (vertex.positionIdx >= 0) newVertex.position = positions[vertex.positionIdx];
						if (vertex.textureCoordsIdx >= 0) newVertex.textureCoords = textureCoords[vertex.textureCoordsIdx];
						if (vertex.normalIdx >= 0) newVertex.normal = normals[vertex.normalIdx];

						this->subMeshes[materialName].indices.push_back(newVertexIndex);
						vertexIndexInBuffer[vertex] = newVertexIndex;

						this->vertices.push_back(newVertex);
					}
				}
			}
		}

		std::cout << "Done loading object file " << filePath << std::endl;
	}
	else {
		std::cout << "RenderData: ERROR: could not open object file " << filePath << std::endl;
	}
}


RenderData::~RenderData() {
	glDeleteBuffers(1, (const GLuint*)&vboId);
	glDeleteVertexArrays(1, (const GLuint*)&vaoId);

	for (auto& elem : subMeshes) {
		elem.second.material.freeTexture();
	}
}
