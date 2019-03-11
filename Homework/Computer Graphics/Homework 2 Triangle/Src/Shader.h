#pragma once

#include <string>

class Shader {
public:
	Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	~Shader();

	void use();
	void setBool(const std::string& key, bool value);
	void setFloat(const std::string& key, float value);
	void setInt(const std::string& key, int value);
	void setVec3(const std::string& key, float* value);

private:
	std::string loadFile(const std::string filename);

	unsigned int id;
};
