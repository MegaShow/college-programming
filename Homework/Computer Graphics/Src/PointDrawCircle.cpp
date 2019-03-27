#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "PointDrawCircle.h"

PointDrawCircle::PointDrawCircle(int radius, int width, int height) {
	this->width = width;
	this->height = height;
	this->radius = radius;
	int size = width * height;
	realPoints = new float[size];
	set(radius);
}

PointDrawCircle::~PointDrawCircle() {
	delete[] realPoints;
}

void PointDrawCircle::draw() {
	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * count, realPoints, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*) 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glPointSize(pointSize);
	glDrawArrays(GL_POINTS, 0, count / 2);
	glBindVertexArray(0);
	glPointSize(1);

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void PointDrawCircle::set(int radius) {
	this->radius = radius;
	count = 0;
	add(0, radius);
	add(0, -radius);
	add(radius, 0);
	add(-radius, 0);
	for (int x = 0, y = radius, d = 3 - 2 * radius; x <= y; x += pointSize) {
		if (d < 0) {
			d += 4 * x + 6;
		} else {
			d += 4 * x - 4 * y + 10;
			y -= pointSize;
		}
		add(x, y);
		add(x, -y);
		add(-x, y);
		add(-x, -y);
		add(y, x);
		add(y, -x);
		add(-y, x);
		add(-y, -x);
	}
}

void PointDrawCircle::setAttr(int size) {
	pointSize = size;
	set(radius);
}

void PointDrawCircle::add(int x, int y) {
	realPoints[count++] = (float) x / (width / 2);
	realPoints[count++] = (float) y / (height / 2);
}
