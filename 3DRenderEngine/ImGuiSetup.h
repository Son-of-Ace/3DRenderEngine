#pragma once

#include <iostream>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp> 
#include <gtc/type_ptr.hpp>
#include "CachedMeshLoader.h"
#include "imgui.h"
#include "ObjFileDialog.h"

inline bool wireFrame = false;
inline bool allowColorAnimation = false;
inline bool allowModelSpin = false;

inline float currentCamZoom = 40;
inline float maxCamZoom = 80;
inline float minCamZoom = 1;

inline float colorAnimationSpeed = 3.0f;

inline glm::vec3 currentRot = glm::vec3(0, 0, 0);
inline float rotFactor = 1.0f;

inline std::wstring objFile;
inline Mesh currentMesh;
inline ImU32 modelColor = 0xFF804F;
inline glm::mat4 view;
inline glm::mat4 model;

inline ImGuiIO* io;

void InitializeImGui(GLFWwindow* window);
void SetupImGui();
void RenderImGui(MeshSerializer& serializer);
void TerminateImGui();
void ResetRotation(glm::vec3& currentRot);