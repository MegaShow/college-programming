// MegaShow
#include "Relation.hpp"

Relation::Relation(BooleanMatrix const & bm) :matrix(bm) {}

BooleanMatrix Relation::getBooleanMatrix() const {
    return matrix;
}

// Operations on Relations
Relation Relation::complementary() const {
    BooleanMatrix tmp(matrix.getRow(), matrix.getColums());
    for(int i = 1; i <= matrix.getRow(); i++) {
        for(int j = 1; j <= matrix.getColums(); j++) {
            tmp.replace(!matrix.getElement(i, j), i, j);
        }
    }
    return Relation(tmp);
}

Relation Relation::inverse() const {
    BooleanMatrix tmp = matrix.transpose();
    return Relation(tmp);
}

Relation Relation::operator&(const Relation &r) {
    BooleanMatrix tmp = matrix & r.matrix;
    return Relation(tmp);
}

Relation Relation::operator|(const Relation &r) {
    BooleanMatrix tmp = matrix | r.matrix;
    return Relation(tmp);
}
