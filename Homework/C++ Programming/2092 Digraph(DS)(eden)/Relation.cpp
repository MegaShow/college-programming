 // MegaShow
#include "Relation.hpp"

Relation::Relation(const BooleanMatrix &bm){
    matrix = new BooleanMatrix(bm);
}

Relation::~Relation(){
    delete matrix;
}