// MegaShow

#include <iostream>
#include "Vector.h"
using namespace std;

Vector::Vector(string _name, int n, int arr[]) :name(_name), dimension(n) {
    cout << "construct a vector called " << name << "." << endl;
    param = new int [dimension];
    for (int i = 0; i < dimension; i++) {
        param[i] = arr[i];
    }
}

Vector::Vector(const Vector &otherVec) :name(otherVec.name), dimension(otherVec.dimension) {
    cout << "copy a vector called " << name << "." << endl;
    param = new int [dimension];
    for (int i = 0; i < dimension; i++) {
        param[i] = otherVec.param[i];
    }
}

Vector::~Vector() {
    cout << "release memory from a vector called " << name << "." << endl;
    delete [] param;
}

void Vector::isEqual(const Vector &v) {
    string str;
    if (name == v.name) {
        str += "same name, ";
    } else {
        str += "different name, ";
    }
    if (dimension == v.dimension) {
        bool flag = true;
        for (int i = 0; i < dimension; i++) {
            if (param[i] != v.param[i]) {
                flag = false;
                break;
            }
        }
        if (flag) {
            str += "same value.";
        } else {
            str += "different value.";
        }
    } else {
        str += "different value.";
    }
    cout << str << endl;
}

void Vector::setName(string _name) {
    name = _name;
}

void Vector::print() {
    cout << name << "(";
    for (int i = 0; i < dimension - 1; i++) {
        cout << param[i] << ", ";
    }
    cout << param[dimension-1] << ")" << endl;
}
