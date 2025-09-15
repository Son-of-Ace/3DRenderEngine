#include "ImGuiSetup.h"

bool ColorPicker3U32(const char* label, ImU32* color, ImGuiColorEditFlags flags = 0) {
	float col[3];
	col[0] = (float)((*color) & 0xFF) / 255.0f;
	col[1] = (float)((*color >> 8) & 0xFF) / 255.0f;
	col[2] = (float)((*color >> 16) & 0xFF) / 255.0f;

	bool result = ImGui::ColorPicker3(label, col, flags);

	if (result) {
		*color = ((ImU32)(col[0] * 255.0f)) | // Red
			((ImU32)(col[1] * 255.0f) << 8) | // Green
			((ImU32)(col[2] * 255.0f) << 16);  // Blue
	}

	return result;
}

void ResetRotation(glm::vec3& currentRot) {
	currentRot = glm::vec3(0, 0, 0);
	model = glm::mat4(1.0f);
}

void InitializeImGui(GLFWwindow* window) {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	io = &ImGui::GetIO();

	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

void SetupImGui() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void RenderImGui(MeshSerializer& serializer) {
	ImGui::SetNextWindowSize(ImVec2(300, io->DisplaySize.y));
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::Begin("3D Renderer Customizer", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
	if (ImGui::Button("Import 3D Model")) {
		std::wstring path = OpenFileDialog();
		if (!path.empty()) {
			objFile = path;
			currentMesh = LoadCachedMesh(objFile, serializer);
		}
	}
	ColorPicker3U32("Pick A Color", &modelColor);
	ImGui::Text("\nCamera Stuff");
	ImGui::DragFloat("Cam Zoom", &currentCamZoom, 0.1f, minCamZoom, maxCamZoom);
	ImGui::Text("\nFun Stuff");
	ImGui::Checkbox("Wire Frame", &wireFrame);
	ImGui::Checkbox("Color Animation", &allowColorAnimation);
	ImGui::Text("\nModel Stuff");
	if (ImGui::DragFloat3("Rotation", glm::value_ptr(currentRot), rotFactor)) {
		model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(currentRot.x), glm::vec3(1, 0, 0));
		model = glm::rotate(model, glm::radians(currentRot.y), glm::vec3(0, 1, 0));
		model = glm::rotate(model, glm::radians(currentRot.z), glm::vec3(0, 0, 1));
	}
	ImGui::Checkbox("Spin Model", &allowModelSpin);
	if (ImGui::Button("Reset Rotation")) {
		ResetRotation(currentRot);
	}

	if (allowModelSpin) {
		float spinSpeed = 30.0f;
		currentRot.x -= spinSpeed * ImGui::GetIO().DeltaTime;
		currentRot.y -= spinSpeed * ImGui::GetIO().DeltaTime;
		currentRot.z -= spinSpeed * ImGui::GetIO().DeltaTime;

		if (currentRot.x < -360.0f) currentRot.x += 360.0f;
		if (currentRot.y < -360.0f) currentRot.y += 360.0f;
		if (currentRot.z < -360.0f) currentRot.z += 360.0f;

		model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(currentRot.x), glm::vec3(1, 0, 0));
		model = glm::rotate(model, glm::radians(currentRot.y), glm::vec3(0, 1, 0));
		model = glm::rotate(model, glm::radians(currentRot.z), glm::vec3(0, 0, 1));
	}

	if (allowColorAnimation) {
		float t = glfwGetTime() * colorAnimationSpeed;
		float r = 0.5f + 0.5f * sin(t);
		float g = 0.5f + 0.5f * sin(t + 2.0f);
		float b = 0.5f + 0.5f * sin(t + 4.0f);

		modelColor = ((ImU32)(r * 255.0f      ))|
					 ((ImU32)(g * 255.0f) << 8 )|
					 ((ImU32)(b * 255.0f) << 16);
	}
	view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -currentCamZoom));
	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void TerminateImGui() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}