#include "ObjLoader.h"

void PrintStatistics() {
	
}

Mesh LoadOBJ(const std::wstring& filePath) {
	Mesh mesh;
	std::vector<glm::vec3> temp_positions;
	std::vector<glm::vec3> temp_normals;
	std::vector<glm::vec2> temp_uvs;

	std::unordered_map<VertexKey, int, VertexKeyHash> vertexMap;

	std::ifstream file(filePath);
	if (!file.is_open()) {
		std::wcerr << L"Failed to open: " << filePath << std::endl;
	}

	if (allowStatisticsPrint) {

	}

	std::string line;
	while (std::getline(file, line)) {
		if (!line.empty() && line.back() == '\r') line.pop_back();
		std::stringstream ss(line);
		std::string prefix;
		ss >> prefix;

		//std::cout << "Line: '" << line << "' Prefix: '" << prefix << "'\n";

		switch (GetPrefixType(prefix)) {
		case V:
			glm::vec3 pos;
			ss >> pos.x >> pos.y >> pos.z;
			temp_positions.push_back(pos); // Push_Back adds an element to the end of the vector, since a vector can grow in size.
			break;
		case VN:
			glm::vec3 norm;
			ss >> norm.x >> norm.y >> norm.z;
			temp_normals.push_back(norm);
			break;
		case VT:
			glm::vec2 uv;
			ss >> uv.x >> uv.y;
			temp_uvs.push_back(uv);
			break;
		case F:
			std::vector<int> faceIndices;
			faceIndices.clear();
			std::string vertexStr;

			while (ss >> vertexStr) {
				std::stringstream vertexSS(vertexStr);
				std::string posIndexStr, uvIndexStr, normalIndexStr;

				std::getline(vertexSS, posIndexStr, '/');
				std::getline(vertexSS, uvIndexStr, '/');
				std::getline(vertexSS, normalIndexStr, '/');

				int posIndex = std::stoi(posIndexStr) - 1;
				int uvIndex = std::stoi(uvIndexStr) - 1;
				int normalIndex = std::stoi(normalIndexStr) - 1;

				Vertex vertex;
				vertex.position = temp_positions[posIndex];
				vertex.uv = temp_uvs[uvIndex];
				vertex.normal = temp_normals[normalIndex];

				VertexKey key{ vertex.position, vertex.normal, vertex.uv };

				auto it = vertexMap.find(key);
				if (it != vertexMap.end()) {
					faceIndices.push_back(it->second);
				}
				else
				{
					mesh.vertices.push_back(vertex);
					int newIndex = (int)mesh.vertices.size() - 1;
					vertexMap[key] = newIndex;
					faceIndices.push_back(newIndex);
				}
			}

			if (faceIndices.size() == 4) {
				mesh.indices.push_back(faceIndices[0]);
				mesh.indices.push_back(faceIndices[1]);
				mesh.indices.push_back(faceIndices[2]);

				mesh.indices.push_back(faceIndices[0]);
				mesh.indices.push_back(faceIndices[2]);
				mesh.indices.push_back(faceIndices[3]);
			}
			else if (faceIndices.size() == 3) {
				mesh.indices.push_back(faceIndices[0]);
				mesh.indices.push_back(faceIndices[1]);
				mesh.indices.push_back(faceIndices[2]);
			}
			break;
		}
	}
	std::cout << "Vertices: " << mesh.vertices.size() << " Indices: " << mesh.indices.size() << "\n";
	return mesh;
}