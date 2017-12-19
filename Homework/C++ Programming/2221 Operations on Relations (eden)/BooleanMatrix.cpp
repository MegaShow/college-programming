//
//  BooleanMatrix.cpp
//  C++
//
//  Created by 李天培 on 16/3/24.
//  Copyright © 2016年 lee. All rights reserved.
//

#include "BooleanMatrix.hpp"

bool BooleanMatrix::replace(matrix_element_type e, int r, int c) {
    if (r <= row && c <= columns && r > 0 && columns > 0) {
        matrix[ELEMENT_POS(r, c)] = e;
        return true;
    }
    return false;
}

BooleanMatrix::BooleanMatrix(const BooleanMatrix & bm) : Matrix(bm) {
}

BooleanMatrix::BooleanMatrix(int r, int c) : Matrix(r, c) {
}

BooleanMatrix BooleanMatrix::operator&(const BooleanMatrix & bm) {
    assert(row == bm.row);
    assert(columns == bm.columns);
    BooleanMatrix temp(row, columns);
    for (int i = 1; i <= row; i++) {
        for (int j = 1; j <= columns; j++) {
            temp.matrix[ELEMENT_POS(i, j)] =
            matrix[ELEMENT_POS(i, j)] & bm.matrix[ELEMENT_POS(i, j)];
        }
    }
    return temp;
}

BooleanMatrix BooleanMatrix::operator|(const BooleanMatrix & bm) {
    assert(row == bm.row);
    assert(columns == bm.columns);
    BooleanMatrix temp(row, columns);
    for (int i = 1; i <= row; i++) {
        for (int j = 1; j <= columns; j++) {
            temp.matrix[ELEMENT_POS(i, j)] =
            matrix[ELEMENT_POS(i, j)] | bm.matrix[ELEMENT_POS(i, j)];
        }
    }
    return temp;
}

BooleanMatrix BooleanMatrix::BooleanProduct(const BooleanMatrix & bm) const {
    assert(getColums() == bm.getRow());
    BooleanMatrix temp(getRow(), bm.getColums());
    for (int i = 1; i <= getRow(); i++) {
        for (int j = 1; j <= bm.getColums(); j++) {
            for (int k = 1; k <= getColums(); k++) {
                temp.matrix[(i - 1) * temp.columns + j - 1] |=
                getElement(i, k) & bm.getElement(k, j);
            }
        }
    }
    return temp;
}

BooleanMatrix BooleanMatrix::transpose() const {
    BooleanMatrix t(columns, row);
    for (int i = 1; i <= row; i++) {
        for (int j = 1; j <= columns; j++) {
            t.matrix[(j - 1) * t.columns + i - 1] = matrix[ELEMENT_POS(i, j)];
        }
    }
    return t;
}

