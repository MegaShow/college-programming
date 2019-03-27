#include <algorithm>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "PointDrawTriangle.h"

PointDrawTriangle::PointDrawTriangle(int points[6], int width, int height) {
	this->width = width;
	this->height = height;
	int size = width * height + 3 * width + 3 * height;
	realPoints = new float[size];
	set(points);
}

PointDrawTriangle::~PointDrawTriangle() {
	delete[] realPoints;
}

void PointDrawTriangle::draw() {
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

void PointDrawTriangle::set(int points[6]) {
	memmove(this->points, points, sizeof(int) * 6);
	count = 0;
	if (!isRasterization) {
		for (int i = 0; i < 3; i++) {
			int j = (i + 1) % 3;
			int x0 = points[i * 2], y0 = points[i * 2 + 1], x1 = points[j * 2], y1 = points[j * 2 + 1];
			bool reserve = std::abs(x0 - x1) < std::abs(y0 - y1);
			if (reserve) {
				std::swap(x0, y0);
				std::swap(x1, y1);
			}
			if (x0 > x1) {
				std::swap(x0, x1);
				std::swap(y0, y1);
			}
			int dy2 = 2 * std::abs(y1 - y0);
			int dy2_dx2 = dy2 - 2 * (x1 - x0);
			int p = dy2 - (x1 - x0);
			int step = y1 - y0 > 0 ? pointSize : -pointSize;
			for (int x = x0, y = y0; x < x1; x += pointSize) {
				if (p <= 0) {
					p = p + dy2;
				} else {
					p = p + dy2_dx2;
					y = y + step;
				}
				if (reserve) {
					add(y, x);
				} else {
					add(x, y);
				}
			}
		}
	} else {
		int minX = std::min({ points[0], points[2], points[4] });
		int minY = std::min({ points[1], points[3], points[5] });
		int maxX = std::max({ points[0], points[2], points[4] });
		int maxY = std::max({ points[1], points[3], points[5] });

		// (y2 - y1) * x + (x1 - x2) * y + (x2 * y1 - y2 * x1) = 0
		int a[3] = { 
			points[5] - points[3], // y2 - y1
			points[5] - points[1], // y2 - y0
			points[3] - points[1]  // y1 - y0
		};
		int b[3] = { 
			points[2] - points[4], // x1 - x2
			points[0] - points[4], // x0 - x2
			points[0] - points[2]  // x0 - x1
		};
		int c[3] = { 
			points[4] * points[3] - points[5] * points[2], // x2 * y1 - y2 * x1
			points[4] * points[1] - points[5] * points[0], // x2 * y0 - y2 * x0
			points[2] * points[1] - points[3] * points[0]  // x1 * y0 - y1 * x0
		};

		for (int k = 0; k < 3; k++) {
			if (a[k] * points[k * 2] + b[k] * points[k * 2 + 1] + c[k] < 0) {
				a[k] = -a[k];
				b[k] = -b[k];
				c[k] = -c[k];
			}
		}

		for (int x = minX; x <= maxX; x += pointSize) {
			for (int y = minY; y <= maxY; y += pointSize) {
				bool flag = true;
				for (int k = 0; k < 3; k++) {
					if (a[k] * x + b[k] * y + c[k] < 0) {
						flag = false;
						break;
					}
				}
				if (flag) {
					add(x, y);
				}
			}
		}
	}
}


void PointDrawTriangle::setAttr(int size, bool rasterization) {
	pointSize = size;
	isRasterization = rasterization;
	set(points);
}

void PointDrawTriangle::add(int x, int y) {
	realPoints[count++] = (float) x / (width / 2);
	realPoints[count++] = (float) y / (height / 2);
}
