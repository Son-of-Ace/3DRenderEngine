#include "GLFWSetup.h"

inline GLFWwindow* gWindow = nullptr;

UniformLocations locs;

int InitGLFW() {
	glfwInit(); // Initialize GLFW (necessary)

	// glfw configuration
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Only need the core openGL profile

	gWindow = glfwCreateWindow(1400, 800, "3D Render Engine", NULL, NULL); // Create a new GLFW window	
	if (gWindow == NULL) {
		std::cout << "Failed to create GLFW window\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(gWindow); // Set the created window as main focus

	glfwSetFramebufferSizeCallback(gWindow, framebuffer_size_callback); // This sets the glfwBufferCallback to our size method that resizes the window dynamically

	InitializeImGui(gWindow);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

double lastTime = glfwGetTime();
int frames = 0;

void GLFWRenderLoop() {
    MeshSerializer serializer(MeshSerializer::Format::JSON);

    unsigned int shaderProgram = InitShaders();
    glUseProgram(shaderProgram);

    glm::vec3 lightDir = glm::normalize(glm::vec3(-1.0f, -1.0f, -1.0f));
    glUniform3fv(glGetUniformLocation(shaderProgram, "lightDir"), 1, glm::value_ptr(lightDir));

    while (!glfwWindowShouldClose(gWindow)) {
        double frameStart = glfwGetTime();

        processInput(gWindow);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        SetupImGui();

        int display_w, display_h;
        glfwGetFramebufferSize(gWindow, &display_w, &display_h);
        int panelWidth = 300;
        glViewport(panelWidth, 0, display_w - panelWidth, display_h);

        float aspect = (float)(display_w - panelWidth) / (float)display_h;
        projection = glm::perspective(glm::radians(45.0f), aspect, 0.1f, 100.0f);

        glUniformMatrix4fv(locs.model, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(locs.view, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(locs.proj, 1, GL_FALSE, glm::value_ptr(projection));

        glm::vec3 shaderColor = glm::vec3(
            ((modelColor) & 0xFF) / 255.0f,
            ((modelColor >> 8) & 0xFF) / 255.0f,
            ((modelColor >> 16) & 0xFF) / 255.0f
        );
        glUniform3fv(glGetUniformLocation(shaderProgram, "modelColor"), 1, glm::value_ptr(shaderColor));

        glBindVertexArray(currentMesh.VAO);
        glPolygonMode(GL_FRONT, wireFrame ? GL_LINE : GL_FILL);
        glDrawElements(GL_TRIANGLES, currentMesh.indices.size(), GL_UNSIGNED_INT, 0);

        RenderImGui(serializer);

        glfwSwapBuffers(gWindow);
        glfwPollEvents();

        frames++;
        double currentTime = glfwGetTime();
        double delta = currentTime - lastTime;

        if (delta >= 1.0) {
            double fps = frames / delta;
            std::cout << "FPS: " << fps << std::endl;

            frames = 0;
            lastTime = currentTime;
        }
    }
}

UniformLocations InitMatrices() {
	// Camera Stuff
	unsigned int shaderProgram = InitShaders();

	model = glm::mat4(1.0f);
	view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -currentCamZoom));
	projection = glm::perspective(glm::radians(45.0f), 1400.0f / 800.0f, 0.1f, 100.0f);

	locs.model = glGetUniformLocation(shaderProgram, "model");
	locs.view = glGetUniformLocation(shaderProgram, "view");
	locs.proj = glGetUniformLocation(shaderProgram, "projection");

	return locs;
}

void TerminateGLFW() {
	glDeleteVertexArrays(1, &currentMesh.VAO);
	glDeleteBuffers(1, &currentMesh.VBO);
	glfwTerminate(); // Clean up all GLFW's resources that were allocated in memory.
	std::cout << "Cleaned up GLFW's allocated memory\n";
}