#version 450 core
in vec3 outColor;

out vec4 FragColor;

void main() {
	FragColor = vec4(outColor.rgb, 1.0f);
}
