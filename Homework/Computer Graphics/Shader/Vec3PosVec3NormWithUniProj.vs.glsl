#version 450 core
layout (location = 0) in vec3 p;
layout (location = 1) in vec3 c;
layout (location = 2) in vec3 n;

out vec3 outPos;
out vec3 outColor;
out vec3 outNorm;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	gl_Position = projection * view * model * vec4(p, 1.0f);
    outPos = vec3(model * vec4(p, 1.0f));
    outColor = c;
    outNorm = n;
}
