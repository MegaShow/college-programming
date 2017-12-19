//
//  Matrix.cpp
//  C++
//
//  Created by 李天培 on 16/3/2.
//  Copyright © 2016年 lee. All rights reserved.
//

#include "Matrix.hpp"

Matrix::Matrix(Matrix const & m) {
    row = m.row;
    columns = m.columns;
    matrix = new matrix_element_type[row * columns];
    for (int i = 1; i <= row; i++) {
        for (int j = 1; j <= columns; j++) {
            matrix[ELEMENT_POS(i, j)] = m.matrix[ELEMENT_POS(i, j)];
        }
    }
}

Matrix::Matrix(int r, int c) {
    row = r > 0 ? r : 1;
    columns = c > 0 ? c : 1;
    matrix = new matrix_element_type[row * columns];
    for (int i = 0; i < row * columns; i++) {
        matrix[i] = 0;
    }
}

Matrix::~Matrix() {
    delete [] matrix;
}

Matrix Matrix::identifyMatrix(int n) {
    Matrix temp = Matrix(n, n);
    for (int i = 1; i <= temp.columns * temp.row; i++) {
        temp.matrix[(i - 1) * n + i - 1] = 1;
    }
    return temp;
}

bool Matrix::replace(Matrix::matrix_element_type e, int r, int c) {
    if (r <= row && c <= columns && r > 0 && columns > 0) {
        matrix[ELEMENT_POS(r, c)] = e;
        return true;
    }
    return false;
}

Matrix::matrix_element_type Matrix::getElement(int r, int c) const {
    return matrix[ELEMENT_POS(r, c)];
}

int Matrix::getRow() const {
    return row;
}

int Matrix::getColums() const {
    return columns;
}

bool Matrix::isDiagonalMatrix() const {
    if (row != columns) {
        return false;
    }
    for (int i = 1; i <= row; i++) {
        for (int j = 1; j <= columns; j++) {
            if (i != j && matrix[ELEMENT_POS(i, j)] != 0) {
                return false;
            }
        }
    }
    return true;
}

bool Matrix::isSquareMatrix() const {
    return row == columns;
}

bool Matrix::isZeroMatrix() const {
    for (int i = 1; i <= row; i++) {
        for (int j = 1; j <= columns; j++) {
            if (matrix[ELEMENT_POS(i, j)] != 0) {
                return false;
            }
        }
    }
    return true;
}

bool Matrix::isSymmetrix() const {
    return *this == transpose();
}

Matrix& Matrix::operator=(const Matrix &m) {
    row = m.row;
    columns = m.columns;
    delete [] matrix;
    matrix = new matrix_element_type[row * columns];

    for (int i = 1; i <= row; i++) {
        for (int j = 1; j <= columns; j++) {
            matrix[ELEMENT_POS(i, j)] = m.matrix[ELEMENT_POS(i, j)];
        }
    }
    return *this;
}

Matrix Matrix::operator+(const Matrix &m) {
    assert(m.row == row);
    assert(m.columns == columns);
    Matrix temp(*this);
    for (int i = 1; i <= row; i++) {
        for (int j = 1; j <= columns; j++) {
            temp.matrix[ELEMENT_POS(i, j)] += m.matrix[ELEMENT_POS(i, j)];
        }
    }
    return temp;
}

Matrix Matrix::operator*(const Matrix &m) {
    assert(columns == m.row);
    Matrix temp(row, m.columns);
    for (int i = 1; i <= temp.row; i++) {
        for (int j = 1; j <= temp.columns; j++) {
            for (int s = 1; s <= columns; s++) {
                temp.matrix[(i - 1) * temp.columns + j - 1] +=
                matrix[ELEMENT_POS(i, s)] *
                m.matrix[(s - 1) * m.columns + j - 1];
            }
        }
    }
    return temp;
}

bool Matrix::operator==(const Matrix &m) const {
    if (row != m.row || columns != m.columns) {
        return false;
    }
    for (int i = 1; i <= row; i++) {
        for (int j = 1; j <= columns; j++) {
            if (matrix[ELEMENT_POS(i, j)] != m.matrix[ELEMENT_POS(i, j)]) {
                return false;
            }
        }
    }
    return true;
}

Matrix Matrix::transpose() const {
    Matrix t(columns, row);
    for (int i = 1; i <= row; i++) {
        for (int j = 1; j <= columns; j++) {
             t.matrix[(j - 1) * t.columns + i - 1] = matrix[ELEMENT_POS(i, j)];
        }
    }
    return t;
}

