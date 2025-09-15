#pragma once

#include "Mesh.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "ObjPrefixType.h"

inline bool allowStatisticsPrint;

Mesh LoadOBJ(const std::wstring& filePath);