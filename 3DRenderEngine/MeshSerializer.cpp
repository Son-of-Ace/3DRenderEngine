#include <iostream>
#include <filesystem>
#include "MeshSerializer.h"
#include <fstream>

namespace fs = std::filesystem;

using nlohmann::json;

MeshSerializer::MeshSerializer(Format f) : format(f) {}

void MeshSerializer::SaveMesh(const Mesh& mesh, const std::wstring& objPath) {
	fs::path path(objPath);
	std::string filename = path.stem().string();

	if (format == Format::JSON) {
		SaveAsJSON(mesh, filename + ".json");
	}
	else if (format == Format::BSON) {
		SaveAsBSON(mesh, filename + ".bson");
	}

	std::cout << "Saved Mesh to: " << std::filesystem::absolute(filename) << std::endl;
}

void MeshSerializer::SaveAsJSON(const Mesh& mesh, const std::string& filename) {
	json j;
	to_json(j, mesh);

	std::ofstream out(filename);
	if (!out.is_open()) throw std::runtime_error("Failed to open file: " + filename);
	out << j.dump(4);
	out.close();
}

void MeshSerializer::SaveAsBSON(const Mesh& mesh, const std::string& filename) {
	json j;
	to_json(j, mesh);

	auto bsonData = json::to_bson(j);
	std::ofstream out(filename, std::ios::binary);
	if (!out.is_open()) throw std::runtime_error("Failed to open file: " + filename);
	out.write(reinterpret_cast<const char*>(bsonData.data()), bsonData.size());
	out.close();
}

Mesh MeshSerializer::LoadFromJSON(const std::string& filename) {
	Mesh mesh;
	std::ifstream in(filename);
	if (!in.is_open()) throw std::runtime_error("Failed to open file: " + filename);

	json j;
	in >> j;
	in.close();

	from_json(j, mesh);
	return mesh;
}