 // MegaShow
#include <cmath>

class base {
public:
    virtual double area() const = 0;
};

class circle : public base {
private:
    double r;
public:
    circle(double r_) : r(r_) {}
    virtual double area() const {
        return acos(-1.0) * r * r;
    }
};

class square : public base {
private:
    double c;
public:
    square(double c_) : c(c_) {}
    virtual double area() const {
        return c * c;
    }
};

class rectangle : public base {
private:
    double a;
    double b;
public:
    rectangle(double a_, double b_) : a(a_), b(b_) {}
    virtual double area() const {
        return a * b;
    }
};

class triangle : public base {
private:
    double a;
    double b;
    double c;
public:
    triangle(double a_, double b_, double c_) : a(a_), b(b_), c(c_) {}
    virtual double area() const {
        double p = (a + b + c) / 2;
        return sqrt(p * (p - a) * (p - b) * (p - c));
    }
};
