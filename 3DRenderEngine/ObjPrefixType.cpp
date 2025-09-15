#include "ObjPrefixType.h"

PrefixType GetPrefixType(const std::string& prefix) {
	if (prefix == "v") return V;
	if (prefix == "vn") return VN;
	if (prefix == "vt") return VT;
	if (prefix == "f") return F;
	return UNKNOWN;
}