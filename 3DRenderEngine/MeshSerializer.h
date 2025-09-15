#pragma once
#include <string>
#include "Mesh.h"
#include <nlohmann/json.hpp>

class MeshSerializer {
public:
	enum class Format { JSON, BSON };

	MeshSerializer(Format f = Format::JSON);

	void SaveMesh(const Mesh& mesh, const std::wstring& objPath);

	Mesh LoadFromJSON(const std::string& filename);
private:
	Format format;

	void SaveAsJSON(const Mesh& mesh, const std::string& objPath);
	void SaveAsBSON(const Mesh& mesh, const std::string& objPath);
};