#include "TransformApplication.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

const std::string TransformApplication::VERTEX_SHADER_FILENAME = "Shader/Vec3PosVec3ColorWithUniProj.vs.glsl";
const std::string TransformApplication::FRAGMENT_SHADER_FILENAME = "Shader/Vec3Color.fs.glsl";

TransformApplication::TransformApplication() 
	: shader(VERTEX_SHADER_FILENAME, FRAGMENT_SHADER_FILENAME) {

	glGenVertexArrays(2, VAO);
	glGenBuffers(2, VBO);

	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	shader.use();
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), (float) 800 / (float) 600, 0.1f, 100.0f);
	shader.setGlmMat4("projection", projection);
}

TransformApplication::~TransformApplication() {
	glDeleteVertexArrays(2, VAO);
	glDeleteBuffers(2, VBO);
}

void TransformApplication::update() {
	ImGui::Begin("Settings", NULL, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Checkbox("Enable Depth Test", &enableDepthTest);
	ImGui::Checkbox("Enable View Radians", &enableViewRadians);
	if (enableDepthTest) {
		glEnable(GL_DEPTH_TEST);
	} else {
		glDisable(GL_DEPTH_TEST);
	}
	ImGui::Text("Transformation Type");
	ImGui::RadioButton("None", &transformType, 0);
	ImGui::RadioButton("Translation", &transformType, 1);
	if (transformType == 1) {
		ImGui::SliderFloat3("Vector3", translationVec3, -1.0f, 1.0f);
	}
	ImGui::RadioButton("Rotation", &transformType, 2);
	if (transformType == 2) {
		ImGui::SliderFloat3("Vector3", rotationVec3, -1.0f, 1.0f);
	}
	ImGui::RadioButton("Scaling", &transformType, 3);
	ImGui::RadioButton("More Transformation", &transformType, 4);
	ImGui::End();
	render();
}

void TransformApplication::render() {
	shader.use();
	glm::mat4 model = glm::scale(glm::mat4(1.0f), glm::vec3(0.25f));
	glm::mat4 view = glm::mat4(1.0f);
	switch (transformType) {
	case 1:
		model = glm::translate(model, glm::vec3(translation * translationVec3[0], translation * translationVec3[1], translation * translationVec3[2]));
		translation += translationStep;
		if (std::abs(translation - 2.0f) < 1e-6 || std::abs(translation + 2.0f) < 1e-6) {
			translationStep = -translationStep;
		}
		break;
	case 2:
		model = glm::rotate(model, (float) glfwGetTime(), glm::vec3(rotationVec3[0], rotationVec3[1], rotationVec3[2]));
		break;
	case 3:
		model = glm::scale(model, glm::vec3(scale));
		scale += scaleStep;
		if (std::abs(scale - 5.0f) < 1e-6 || std::abs(scale - 0.5f) < 1e-6) {
			scaleStep = -scaleStep;
		}
		break;
	case 4:
		model = glm::scale(model, glm::vec3(moreScale));
		moreScale += moreScaleStep;
		if (std::abs(moreScale - 1.0f) < 1e-6 || std::abs(moreScale - 0.6f) < 1e-6) {
			moreScaleStep = -moreScaleStep;
		}
		break;
	}
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -7.0f));
	if (enableViewRadians) {
		view = glm::rotate(view, glm::radians(-45.0f), glm::vec3(-1.0f, 1.0f, 0.0f));
	}

	shader.setGlmMat4("model", model);
	shader.setGlmMat4("view", view);

	glBindVertexArray(VAO[0]);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

	if (transformType == 4) {
		glm::mat4 model = glm::scale(glm::mat4(1.0f), glm::vec3(0.25f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		model = glm::rotate(model, (float) glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(60.0f, 0, 0));
		model = glm::rotate(model, 10 * (float) glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
		shader.setGlmMat4("model", model);

		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
	}
}
