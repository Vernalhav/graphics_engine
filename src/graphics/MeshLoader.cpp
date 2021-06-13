#include "MeshLoader.h"
#include "../misc/utils.h"

#include <fstream>
#include <iostream>
#include <unordered_map>


Mesh* MeshLoader::loadMesh(const std::string& filePath) {

	std::ifstream objFile;
	objFile.open(filePath);

	if (objFile.is_open()) {

		std::vector<glm::vec3> positions;
		std::vector<glm::vec2> textureCoords;
		std::vector<glm::vec3> normals;
		std::vector<Face> faces;

		std::string material;
		for (std::string line, int lineNum = 1; std::getline(objFile, line); lineNum++) {
			std::vector<std::string> lineTokens = utils::split(line);
			if (lineTokens.size() == 0 || lineTokens[0][0] == '#') continue;

			if (lineTokens[0] == "v") positions.push_back(parseVertexPosition(lineTokens));
			if (lineTokens[0] == "vn") normals.push_back(parseNormal(lineTokens));
			if (lineTokens[0] == "vt") textureCoords.push_back(parseTextureCoords(lineTokens));
			if (lineTokens[0] == "f") faces.push_back(parseFace(lineTokens));
			if (lineTokens[0] == "usemtl") material = lineTokens[1];
		}

		Mesh* mesh = new Mesh();
		mesh->material = material;

		// As an optimization, we'll try to reuse as many vertices as possible by
		// indexing, therefore we must know which vertices have already been used.
		
		// Mapping between unique vertex attribute indices and the vertex index in the vertex array
		std::unordered_map<VertexIndexInfo, int> vertexIndexInBuffer;

		for (Face face : faces) {
			for (VertexIndexInfo vertex : face) {
				if (vertexIndexInBuffer.count(vertex)) {
					mesh->indices.push_back(vertexIndexInBuffer[vertex]);
				}
				else {
					int newVertexIndex = mesh->vertices.size();

					Vertex newVertex;
					if (vertex.positionIdx >= 0) newVertex.position = positions[vertex.positionIdx];
					if (vertex.textureCoordsIdx >= 0) newVertex.textureCoords = textureCoords[vertex.textureCoordsIdx];
					if (vertex.normalIdx >= 0) newVertex.normal = positions[vertex.normalIdx];

					mesh->indices.push_back(newVertexIndex);
					vertexIndexInBuffer[vertex] = newVertexIndex;
					
					mesh->vertices.push_back(newVertex);
				}
			}
		}

		return mesh;
	}
	else {
		std::cout << "ERROR: loadMesh: could not open object file " << filePath << std::endl;
		return nullptr;
	}

	objFile.close();
}


/// <summary>
/// Using an unnamed namespace to declare
/// "private" funcions that are only accessible
/// in this .cpp file
/// </summary>
namespace {

	using Face = std::vector<VertexIndexInfo>;

	/// <summary>
	/// Position, normal and texture coordinate index
	/// of a face vertex read from an .obj file.
	/// Indices are 0-based.
	/// </summary>
	struct VertexIndexInfo {
		int positionIdx;
		int textureCoordsIdx;
		int normalIdx;

		VertexIndexInfo() : positionIdx(-1), textureCoordsIdx(-1), normalIdx(-1) { }

		VertexIndexInfo(int posIdx, int uvCoordsIdx, int normalIdx)
			: positionIdx(posIdx), textureCoordsIdx(uvCoordsIdx), normalIdx(normalIdx) { };

		bool operator==(const VertexIndexInfo& other) const {
			return positionIdx == other.positionIdx &&
				textureCoordsIdx == other.textureCoordsIdx &&
				normalIdx == other.normalIdx;
		}
	};

	Face parseFace(const std::vector<std::string>& lineTokens) {
		Face face;

		for (int i = 1; i < lineTokens.size(); i++) {
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
}
