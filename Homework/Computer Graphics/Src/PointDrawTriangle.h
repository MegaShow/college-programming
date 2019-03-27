#pragma once

class PointDrawTriangle {
public:
	PointDrawTriangle(int points[6], int width, int height);
	~PointDrawTriangle();
	void draw();
	void set(int points[6]);
	void setAttr(int size, bool rasterization);

private:
	void add(int x, int y);

	int width;
	int height;
	int pointSize = 1;
	bool isRasterization = false;
	int count = 0;
	int points[6];
	float* realPoints = nullptr;
};
