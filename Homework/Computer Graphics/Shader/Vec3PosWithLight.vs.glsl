#version 450 core
layout (location = 0) in vec3 p;
layout (location = 1) in vec3 c;
layout (location = 2) in vec3 n;

out vec3 outColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform bool needAmbient;
uniform bool needDiffuse;
uniform bool needSpecular;
uniform float ambientFactor;
uniform float specularFactor;
uniform int specularPow;

void main() {
	gl_Position = projection * view * model * vec4(p, 1.0f);

    vec3 outPos = vec3(model * vec4(p, 1.0));
    vec3 outNorm = mat3(transpose(inverse(model))) * n;

    vec3 ambient = ambientFactor * lightColor;
    
    vec3 norm = normalize(outNorm);
    vec3 lightDir = normalize(lightPos - outPos);
    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = diff * lightColor;

    vec3 viewDir = normalize(viewPos - outPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), specularPow);
    vec3 specular = specularFactor * spec * lightColor;

    vec3 factor = vec3(0.0f);
    if (needAmbient) factor += ambient;
    if (needDiffuse) factor += diffuse;
    if (needSpecular) factor += specular;
    outColor = factor * c;
}
