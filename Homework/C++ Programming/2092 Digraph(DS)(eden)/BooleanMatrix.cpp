// MegaShow
#include "BooleanMatrix.hpp"


BooleanMatrix::BooleanMatrix(const BooleanMatrix & m) : Matrix(m) {}

BooleanMatrix::BooleanMatrix(int r, int c) : Matrix(r, c) {}

bool BooleanMatrix::replace(BooleanMatrix::matrix_element_type e, int r, int c){
    return Matrix::replace(e, r, c);
}

BooleanMatrix BooleanMatrix::operator&(const BooleanMatrix & m){
    BooleanMatrix tmp(row, columns);
    for(int i = 0; i < row * columns; i++){
        if(matrix[i] && m.matrix[i])
            tmp.matrix[i] = true;
    }
    return tmp;
}

BooleanMatrix BooleanMatrix::operator|(const BooleanMatrix & m){
    BooleanMatrix tmp(row, columns);
    for(int i = 0; i < row * columns; i++){
        if(matrix[i] || m.matrix[i])
            tmp.matrix[i] = true;
    }
    return tmp;
}

BooleanMatrix BooleanMatrix::BooleanProduct(const BooleanMatrix & m) const{
    BooleanMatrix tmp(row, m.columns);
    for (int i = 1; i <= tmp.row; i++) {
        for (int j = 1; j <= tmp.columns; j++) {
            for (int s = 1; s <= columns; s++) {
                if(matrix[ELEMENT_POS(i, s)] * m.matrix[(s - 1) * m.columns + j - 1]){
                    tmp.matrix[(i - 1) * tmp.columns + j - 1] = true;
                    break;
                }
            }
        }
    }
    return tmp;
}