 // MegaShow

#ifndef RELATION_HPP_
#define RELATION_HPP_

#include "BooleanMatrix.hpp"

class Relation{
  protected:
    BooleanMatrix* matrix;
  public:
    Relation(const BooleanMatrix &bm);
    ~Relation();
};

#endif