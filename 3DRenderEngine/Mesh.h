#pragma once
#include <vector>
#include <glm.hpp>
#include <nlohmann/json.hpp>

using nlohmann::json;

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 uv;

	bool operator==(const Vertex& other) const {
		return position == other.position && normal == other.normal && uv == other.uv;
	}
};

struct VertexKey {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 uv;

	bool operator==(const VertexKey& other) const {
		return position == other.position && normal == other.normal && uv == other.uv;
	}
};

struct VertexKeyHash {
	std::size_t operator()(const VertexKey& v) const {
		auto h1 = std::hash<float>()(v.position.x) ^ std::hash<float>()(v.position.y) ^ std::hash<float>()(v.position.z);
		auto h2 = std::hash<float>()(v.normal.x) ^ std::hash<float>()(v.normal.y) ^ std::hash<float>()(v.normal.z);
		auto h3 = std::hash<float>()(v.uv.x) ^ std::hash<float>()(v.uv.y);
		return h1 ^ (h2 << 1) ^ (h3 << 2);
	}
};

struct Mesh {
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	unsigned int VAO, VBO, EBO;
};

inline void to_json(json& j, const Vertex& v) {
	j = json{
		{"position", {v.position.x, v.position.y, v.position.z}},
		{"normal", {v.normal.x, v.normal.y, v.normal.z}},
		{"uv", {v.uv.x, v.uv.y}}
	};
}

inline void to_json(json& j, const Mesh& mesh) {
	j = json{
		{"vertices", mesh.vertices},
		{"indices", mesh.indices}
	};
}

inline void from_json(const json& j, Vertex& v) {
	v.position.x = j.at("position")[0];
	v.position.y = j.at("position")[1];
	v.position.z = j.at("position")[2];

	v.normal.x = j.at("normal")[0];
	v.normal.y = j.at("normal")[1];
	v.normal.z = j.at("normal")[2];

	v.uv.x = j.at("uv")[0];
	v.uv.y = j.at("uv")[1];
}

inline void from_json(json& j, Mesh& mesh) {
	j.at("vertices").get_to(mesh.vertices);
	j.at("indices").get_to(mesh.indices);
}