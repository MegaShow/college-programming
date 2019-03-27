#include <iostream>
#include <fstream>
#include <sstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"

Shader::Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
	int success;
	char log[512];

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	std::string vertexShaderSourceWrapper = loadFile(vertexShaderPath);
	const char* vertexShaderSource = vertexShaderSourceWrapper.c_str();
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, log);
		std::cout << "Compile vertex shader failed." << std::endl << log << std::endl;
	}

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	std::string fragmentShaderSourceWrapper = loadFile(fragmentShaderPath);
	const char* fragmentShaderSource = fragmentShaderSourceWrapper.c_str();
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, log);
		std::cout << "Compile fragment shader failed." << std::endl << log << std::endl;
	}

	id = glCreateProgram();
	glAttachShader(id, vertexShader);
	glAttachShader(id, fragmentShader);
	glLinkProgram(id);
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(id, 512, NULL, log);
		std::cout << "Link shaders failed." << std::endl << log << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader() {
	glDeleteProgram(id);
}

void Shader::use() {
	glUseProgram(id);
}

void Shader::setBool(const std::string& key, bool value) {
	glUniform1i(glGetUniformLocation(id, key.c_str()), (int) value);
}

void Shader::setFloat(const std::string& key, float value) {
	glUniform1f(glGetUniformLocation(id, key.c_str()), value);
}

void Shader::setInt(const std::string& key, int value) {
	glUniform1i(glGetUniformLocation(id, key.c_str()), value);
}

void Shader::setVec3(const std::string& key, float* value) {
	glUniform3fv(glGetUniformLocation(id, key.c_str()), 1, value);
}

std::string Shader::loadFile(const std::string filename) {
	std::ifstream in(filename);
	if (!in) {
		std::cout << "File \"" << filename << "\" not found." << std::endl;
	}
	std::stringstream buffer;
	std::string str;
	buffer << in.rdbuf();
	in.close();
	return buffer.str();
}
