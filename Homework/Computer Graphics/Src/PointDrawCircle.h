#pragma once

class PointDrawCircle {
public:
    PointDrawCircle(int radius, int width, int height);
    ~PointDrawCircle();
    void draw();
    void set(int radius);
    void setAttr(int size);

private:
    void add(int x, int y);

    int width;
    int height;
    int pointSize = 1;
    int radius;
    int count = 0;
    float* realPoints = nullptr;
};
