//
//  Matrix.hpp
//  C++
//
//  Created by 李天培 on 16/3/2.
//  Copyright © 2016年 lee. All rights reserved.
//

#ifndef Matrix_hpp
#define Matrix_hpp

#include <stdio.h>
#include <iostream>
#include <assert.h>

#define ELEMENT_POS(x,y) (x - 1) * columns + y - 1

class Matrix {
private:
    // matrix element type
    typedef int matrix_element_type;
protected:
    int row, columns;
    matrix_element_type* matrix;
    
public:
    // copy constructor
    Matrix(Matrix const &);
    // creat a empty matrix with row and column, fill the matrix by 0
    Matrix(int r, int c);
    // delete
    ~Matrix();
    // creat a identify matrix with n which is row and column
    static Matrix identifyMatrix(int n);
    
    // replace the element in specific position and return true
    // return false if can't replace
    bool replace(matrix_element_type e, int r, int c);
    bool isDiagonalMatrix() const;
    bool isZeroMatrix() const;
    bool isSquareMatrix() const;
    bool isSymmetrix() const;
    
    void display() const {
        for (int i = 1; i <= row; i++) {
            for (int j = 1; j <= columns; j++) {
                std::cout << matrix[ELEMENT_POS(i, j)] << " ";
            }
            std::cout << std::endl;
        }
    }
    
    Matrix transpose() const;
    
    Matrix& operator=(const Matrix & m);
    Matrix operator+(const Matrix & m);
    Matrix operator*(const Matrix & m);
    
    bool operator==(const Matrix & m) const;
    
    
    int getRow() const;
    int getColums() const;
    matrix_element_type getElement(int r, int c) const;
};

#endif /* Matrix_hpp */

