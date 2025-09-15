#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <iostream>
#include "SizeCallback.h"
#include "ImGuiSetup.h"
#include "MeshSerializer.h"
#include "ShaderSetup.h"

inline glm::mat4 projection;

struct UniformLocations {
	unsigned int model, view, proj;
};

int InitGLFW();
void GLFWRenderLoop();
UniformLocations InitMatrices();
void TerminateGLFW();