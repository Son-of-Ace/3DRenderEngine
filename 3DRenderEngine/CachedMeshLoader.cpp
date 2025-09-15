#include "CachedMeshLoader.h"

namespace fs = std::filesystem;

Mesh LoadCachedMesh(const std::wstring& filePath, MeshSerializer& serializer) {
	fs::path objPathFs(filePath);
	fs::path jsonPath = objPathFs.parent_path() / (objPathFs.stem().string() + ".json");

	Mesh mesh;

	if (fs::exists(jsonPath)) {
		std::cout << "Loading cached mesh: " << jsonPath << std::endl;
		mesh = serializer.LoadFromJSON(jsonPath.string());
	}
	else
	{
		mesh = LoadOBJ(filePath);
		serializer.SaveMesh(mesh, filePath);
	}

	SetupMesh(mesh);
	return mesh;
}