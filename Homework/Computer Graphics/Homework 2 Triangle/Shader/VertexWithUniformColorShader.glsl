#version 460 core

layout (location = 0) in vec3 p;

uniform vec3 uniColor;

out vec3 outColor;

void main() {
	gl_Position = vec4(p.xyz, 1.0);
	outColor = uniColor;
}
