#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <string.h>
using namespace std;

class Matrix {
    public:
        Matrix() {
            name = "";
            width = height = 0;
            param = NULL;
        }
        Matrix(string, int, int, int**);
        Matrix(const Matrix &);
        ~Matrix();
        void setName(string newName) {
            name = newName;
        }
        string getName() {
            return name;
        }
        void print() {
            cout << name << " = [\n";
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    if (j == width-1) cout << param[i][j];
                    else cout << param[i][j] << ", ";
                }
                cout << "\n";
            }
            cout << "]\n";
        }
        // overload operator
        bool operator ==(const Matrix&);
        bool operator !=(const Matrix&);
        void operator +=(const Matrix&);
        void operator -=(const Matrix&);
        Matrix operator *(const Matrix&);
    private:
        string name;
        int width, height, **param;
};

#endif
