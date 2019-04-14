#version 450 core
layout (location = 0) in vec3 p;
layout (location = 1) in vec3 inColor;

out vec3 outColor;

void main() {
	gl_Position = vec4(p.xyz, 1.0);
	outColor = inColor;
}
