#version 450 core
layout (location = 0) in vec3 p;
layout (location = 1) in vec3 c;

out vec3 outColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	gl_Position = projection * view * model * vec4(p, 1.0f);
	outColor = c;
}
