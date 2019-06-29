#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 outPos;
out vec3 outNorm;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    outPos = vec3(model * vec4(aPos, 1.0));
    outNorm = mat3(transpose(inverse(model))) * aNormal;

    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
