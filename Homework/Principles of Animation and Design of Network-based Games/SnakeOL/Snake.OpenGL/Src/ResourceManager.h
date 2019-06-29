#pragma once

#include <map>
#include <string>

#include "Model.h"
#include "Shader.h"

class ResourceManager {
public:
    static Shader& getShader(const std::string& name);
    static Shader& loadShader(const std::string& name, const std::string& vs, const std::string& fs);

    static Model& getModel(const std::string& name);
    static Model& loadModel(const std::string& name, const std::string& file);

    static void clear();

private:
    ResourceManager() {}

    static std::map<const std::string, Shader> shaders;
    static std::map<const std::string, Model> models;
};
