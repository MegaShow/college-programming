#version 450 core

layout (location = 0) in vec2 p;

uniform vec3 uniColor;

out vec3 outColor;

void main() {
	gl_Position = vec4(p.xy, 1.0, 1.0);
	outColor = uniColor;
}
