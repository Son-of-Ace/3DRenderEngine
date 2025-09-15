#include <iostream>

#include "GLFWSetup.h"
#include "GladSetup.h"

namespace fs = std::filesystem;
using nlohmann::json;

int main() {
	InitGLFW();
	InitGlad();
	InitShaders();

	// Camera Matrices
	InitMatrices();
	// Render loop
	GLFWRenderLoop();
	// Terminate ImGui
	TerminateImGui();
	// Terminate GLFW
	TerminateGLFW();
}