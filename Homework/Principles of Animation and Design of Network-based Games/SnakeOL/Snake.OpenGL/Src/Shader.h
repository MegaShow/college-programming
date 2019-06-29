#pragma once

#include <string>

#include <glm/glm.hpp>

class Shader {
public:
    ~Shader();

    void program(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
    void use();
    void setBool(const std::string& key, bool value);
    void setFloat(const std::string& key, float value);
    void setInt(const std::string& key, int value);
    void setVec3(const std::string& key, float* value);
    void setGlmVec3(const std::string& key, glm::vec3& value);
    void setGlmMat4(const std::string& key, glm::mat4& value);

private:
    std::string loadFile(const std::string filename);

    unsigned int id;
    bool isProgram = false;
};
