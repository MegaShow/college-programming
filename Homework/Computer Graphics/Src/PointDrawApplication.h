#pragma once

#include <string>

#include "Application.h"
#include "PointDrawTriangle.h"
#include "PointDrawCircle.h"
#include "Shader.h"

class PointDrawApplication: public Application {
public:
	PointDrawApplication();
	~PointDrawApplication();
	virtual void update();

private:
	void render();

	Shader shader;

	int objectType = 0;
	int pointSize = 1;
	bool rasterization = false;
	int points[6] = { -300, -200, 0, 200, 150, -150 };
	int radius = 100;

	PointDrawTriangle triangle;
	PointDrawCircle circle;

	static const std::string VERTEX_SHADER_FILENAME;
	static const std::string FRAGMENT_SHADER_FILENAME;
};
