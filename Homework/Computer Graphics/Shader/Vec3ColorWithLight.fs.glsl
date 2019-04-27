#version 450 core
in vec3 outPos;
in vec3 outColor;
in vec3 outNorm;

out vec4 FragColor;

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
    FragColor = vec4(factor * outColor, 1.0f);
}
