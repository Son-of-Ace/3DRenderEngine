#pragma once

inline const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos; // Position input
layout (location = 1) in vec3 aNormal;

out vec3 fragNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	fragNormal = mat3(transpose(inverse(model))) * aNormal;
	gl_Position = projection * view * model * vec4(aPos, 1.0); // Set final vertex position
}
)";

// Fragment shader source code
inline const char* fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor; // Ouput Color

in vec3 fragNormal;

uniform vec3 modelColor; // Color of the model
uniform vec3 lightDir;

void main() {
	float ambientStrength = 0.2;
	vec3 ambient = ambientStrength * modelColor;

	vec3 norm = normalize(fragNormal);
	float diff = max(dot(norm, normalize(-lightDir)), 0.0);
	vec3 diffuse = diff * modelColor;

	vec3 color = ambient + diffuse;
	FragColor = vec4(color, 1.0);
}
)";