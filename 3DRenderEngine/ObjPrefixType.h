#pragma once
#include <iostream>

enum PrefixType { V, VN, VT, F, UNKNOWN };

PrefixType GetPrefixType(const std::string& prefix);