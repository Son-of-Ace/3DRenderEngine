#include "ObjFileDialog.h"

std::wstring OpenFileDialog() {
	wchar_t filename[MAX_PATH] = L"";
	const wchar_t filter[] = L"OBJ Files\0*.obj\0All Files\0*.*\0";

	OPENFILENAMEW ofn;
	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn);
	ofn.lpstrFilter = filter;
	ofn.lpstrFile = filename;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrTitle = L"Select a 3D Model";

	if (GetOpenFileNameW(&ofn)) {
		return std::wstring(filename);
	}

	return L"";
}