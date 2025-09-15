#pragma once

#include <iostream>
#include "Mesh.h"
#include "MeshSerializer.h"
#include "ObjLoader.h"
#include "MeshSetup.h"
#include "nlohmann/json.hpp"

Mesh LoadCachedMesh(const std::wstring& filePath, MeshSerializer& serializer);