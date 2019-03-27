#include <iostream>
#include <fstream>
#include <sstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>

#include "TriangleApplication.h"

const std::string TriangleApplication::VERTEX_SHADER_FILENAME = "Shader/Vec3PosVec3Color.vs.glsl";
const std::string TriangleApplication::VERTEX_WITH_UNIFORM_COLOR_SHADER_FILENAME = "Shader/Vec3PosWithUniColor.vs.glsl";
const std::string TriangleApplication::FRAGMENT_SHADER_FILENAME = "Shader/Vec3Color.fs.glsl";

TriangleApplication::TriangleApplication()
	: shader(VERTEX_SHADER_FILENAME, FRAGMENT_SHADER_FILENAME),
	shaderWithUniColor(VERTEX_WITH_UNIFORM_COLOR_SHADER_FILENAME, FRAGMENT_SHADER_FILENAME) {

	glGenVertexArrays(5, VAOs);
	glGenBuffers(5, VBOs);
	glGenBuffers(1, &EBO);
	// Point
	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pointVertices), pointVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	// Line
	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(lineVertices), lineVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	// Colorful Triangle
	glBindVertexArray(VAOs[2]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colorfulTriVertices), colorfulTriVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	// Single-color Triangle
	glBindVertexArray(VAOs[3]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(singleColorTriVertices), singleColorTriVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	// More Triangle
	glBindVertexArray(VAOs[4]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[4]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(moreTriVertices), moreTriVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(moreTriIndices), moreTriIndices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	shaderWithUniColor.use();
	shaderWithUniColor.setVec3("uniColor", color);
}

TriangleApplication::~TriangleApplication() {
	glDeleteVertexArrays(5, VAOs);
	glDeleteBuffers(5, VBOs);
	glDeleteBuffers(1, &EBO);
}

void TriangleApplication::update() {
	ImGui::Begin("Settings", NULL, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::RadioButton("Point", &objectType, 0);
	ImGui::RadioButton("Line", &objectType, 1);
	ImGui::RadioButton("Colorful Triangle", &objectType, 2);
	ImGui::RadioButton("Single-color Triangle", &objectType, 3);
	if (objectType == 3) {
		if (ImGui::ColorEdit3("Triangle Color", color)) {
			shaderWithUniColor.setVec3("uniColor", color);
		}
	}
	ImGui::RadioButton("More Triangle", &objectType, 4);
	if (objectType == 4) {
		if (ImGui::ColorEdit3("Triangle Color", color)) {
			shaderWithUniColor.setVec3("uniColor", color);
		}
	}
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();
	render();
}

void TriangleApplication::render() {
	switch (objectType) {
	case 0:
		shader.use();
		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_POINTS, 0, 1);
		break;
	case 1:
		shader.use();
		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_LINES, 0, 2);
		break;
	case 2:
		shader.use();
		glBindVertexArray(VAOs[2]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		break;
	case 3:
		shaderWithUniColor.use();
		glBindVertexArray(VAOs[3]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		break;
	case 4:
		shaderWithUniColor.use();
		glBindVertexArray(VAOs[4]);
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		break;
	}
}
