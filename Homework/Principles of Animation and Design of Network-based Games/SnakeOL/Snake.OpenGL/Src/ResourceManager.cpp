#include "ResourceManager.h"

std::map<const std::string, Shader> ResourceManager::shaders;
std::map<const std::string, Model> ResourceManager::models;

Shader& ResourceManager::getShader(const std::string& name) {
    return shaders[name];
}

Shader& ResourceManager::loadShader(const std::string& name, const std::string& vs, const std::string& fs) {
    shaders[name].program(vs, fs);
    return shaders[name];
}

Model& ResourceManager::getModel(const std::string& name) {
    return models[name];
}

Model& ResourceManager::loadModel(const std::string& name, const std::string& file) {
    models[name] = Model(file);
    return models[name];
}

void ResourceManager::clear() {
    shaders.clear();
    models.clear();
}
