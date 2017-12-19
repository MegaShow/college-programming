 // MegaShow
#include "Digraph.hpp"

int Digraph::getSetElePos(int ele){
    for(int i = 1; i <= set.getSize(); i++){
        if(ele == set.get(i))
            return i;
    }
    return 0;
}

Digraph::Digraph(BooleanMatrix const &m, Set const &s) :Relation(m){
    set = s;
}

int Digraph::inDegree(int var){
    int pos = getSetElePos(var);
    if(pos == 0)
        return -1;
    int count = 0;
    for(int i = 1; i <= matrix->getRow(); i++){
        if(matrix->getElement(i, pos))
            count++;
    }
    return count;
}

int Digraph::outDegree(int var){
    int pos = getSetElePos(var);
    if(pos == 0)
        return -1;
    int count = 0;
    for(int i = 1; i <= matrix->getColums(); i++){
        if(matrix->getElement(pos, i))
            count++;
    }
    return count;
}
    
Digraph Digraph::pathOfLength(int n){
    BooleanMatrix tmp = *matrix;
    for(int i = 1; i < n; i++){
        tmp = tmp.BooleanProduct(*matrix);
    }
    return Digraph(tmp, set);
}

// Properties of Relations.    
bool Digraph::isReflexive() const{
    for(int i = 1; i <= matrix->getRow(); i++){
        if(matrix->getElement(i, i) == false)
            return false;
    }
    return true;
}

bool Digraph::isIrreflexive() const{
    for(int i = 1; i <= matrix->getRow(); i++){
        if(matrix->getElement(i, i))
            return false;
    }
    return true;
}

bool Digraph::isSymmetric() const{
    return matrix->isSymmetrix();
}

bool Digraph::isAsymmetric() const{
    for(int i = 1; i <= matrix->getRow(); i++){
        for(int j = 1; j <= matrix->getColums(); j++){
            if(matrix->getElement(i, j) && matrix->getElement(j, i))
                return false;
        }
    }
    return true;
}

bool Digraph::isAntisymmetric() const{
    for(int i = 1; i <= matrix->getRow(); i++){
        for(int j = 1; j <= matrix->getColums(); j++){
            if(matrix->getElement(i, j) && matrix->getElement(j, i) && i != j)
                return false;
        }
    }
    return true;
}
    
bool Digraph::isTransitive() const{
    int size = matrix->getRow();
    for(int i = 1; i <= size; i++){
        for(int j = 1; j <= size; j++){
            if(matrix->getElement(i, j)){
                for(int k = 1; k <= size; k++){
                    if(matrix->getElement(j, k) && !matrix->getElement(i, k))
                        return false;
                }
            }
        }
    }
    return true;
}
    
BooleanMatrix Digraph::getBooleanMatrix() const{
    return *matrix;
}
