// MegaShow
#include "BinaryRelation.hpp"

int BinaryRelation::getSetElePos(int var) {
    for(int i = 1; i <= set.getSize(); i++) {
        if(set.get(i) == var)
            return i;
    }
    return 0;
}

BinaryRelation::BinaryRelation(BooleanMatrix const &m, Set const &s) :Relation(m), set(s) {}

int BinaryRelation::inDegree(int var) {
    int pos = getSetElePos(var);
    if(pos == 0)
        return -1;
    int count = 0;
    for(int i = 1; i <= matrix.getRow(); i++) {
        count += matrix.getElement(i, pos);
    }
    return count;
}

int BinaryRelation::outDegree(int var) {
    int pos = getSetElePos(var);
    if(pos == 0)
        return -1;
    int count = 0;
    for(int i = 1; i <= matrix.getColums(); i++) {
        count += matrix.getElement(pos, i);
    }
    return count;
}

BinaryRelation BinaryRelation::pathOfLength(int n) {
    BooleanMatrix tmp = matrix;
    for(int i = 1; i < n; i++) {
        tmp = tmp.BooleanProduct(matrix);
    }
    return BinaryRelation(tmp, set);
}

// Properties of Relations.    
bool BinaryRelation::isReflexive() const {
    for(int i = 1; i <= matrix.getRow(); i++) {
        if(matrix.getElement(i, i) == false)
            return false;
    }
    return true;
}

bool BinaryRelation::isIrreflexive() const {
    for(int i = 1; i <= matrix.getRow(); i++) {
        if(matrix.getElement(i, i))
            return false;
    }
    return true;
}

bool BinaryRelation::isSymmetric() const {
    return matrix == matrix.transpose();
}

bool BinaryRelation::isAsymmetric() const {
    for(int i = 1; i <= matrix.getRow(); i++) {
        for(int j = 1; j <= matrix.getColums(); j++) {
            if(matrix.getElement(i, j) && matrix.getElement(j, i))
                return false;
        }
    }
    return true;
}

bool BinaryRelation::isAntisymmetric() const {
    for(int i = 1; i <= matrix.getRow(); i++) {
        for(int j = 1; j <= matrix.getColums(); j++) {
            if(matrix.getElement(i, j) && matrix.getElement(j, i) && i != j)
                return false;
        }
    }
    return true;
}

bool BinaryRelation::isTransitive() const {
    int size = matrix.getRow();
    for(int i = 1; i <= size; i++) {
        for(int j = 1; j <= size; j++) {
            if(matrix.getElement(i, j)) {
                for(int k = 1; k <= size; k++) {
                    if(matrix.getElement(j, k) && !matrix.getElement(i, k))
                        return false;
                }
            }
        }
    }
    return true;
}

bool BinaryRelation::isEquivalence() const {
    return isReflexive() && isSymmetric() && isTransitive();
}

BinaryRelation BinaryRelation::composition(const BinaryRelation &r) {
    int size = matrix.getRow();
    BooleanMatrix tmp(size, size);
    for(int i = 1; i <= size; i++) {
        for(int j = 1; j <= size; j++) {
            if(r.matrix.getElement(i, j)) {
                for(int k = 1; k <= size; k++) {
                    if(matrix.getElement(j, k)) {
                        tmp.replace(true, i, k);
                    }
                }
            }
        }
    }
    return BinaryRelation(tmp, set);
}

BinaryRelation BinaryRelation::reflexiveClosure() const {
    BooleanMatrix tmp = matrix;
    for(int i = 1; i <= matrix.getRow(); i++) {
        tmp.replace(true, i, i);
    }
    return BinaryRelation(tmp, set);
}

BinaryRelation BinaryRelation::symmetricClosure() const {
    BooleanMatrix tmp(matrix);
    for(int i = 1; i <= matrix.getRow(); i++) {
        for(int j = 1; j <= matrix.getColums(); j++) {
            if(tmp.getElement(i, j))
                tmp.replace(true, j, i);
        }
    }
    return BinaryRelation(tmp, set);
}

BinaryRelation BinaryRelation::transitiveClosure() const {
    BooleanMatrix tmp = matrix;
    for(int k = 1; k <= tmp.getRow(); k++) {
        for(int i = 1; i <= tmp.getRow(); i++) {
            for(int j = 1; j <= tmp.getRow(); j++) {
                if(tmp.getElement(i, k) && tmp.getElement(k, j))
                    tmp.replace(true, i, j);
            }
        }
    }
    return BinaryRelation(tmp, set);
}
