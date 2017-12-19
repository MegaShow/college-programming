//
//  BinaryRelation.hpp
//  C++
//
//  Created by 李天培 on 16/4/7.
//  Copyright © 2016年 lee. All rights reserved.
//

#ifndef BINARYRELATION_HPP_
#define BINARYRELATION_HPP_

#include <stdio.h>
#include "BooleanMatrix.hpp"
#include "Set.hpp"
#include "Relation.hpp"

class BinaryRelation: public Relation {
private:
    Set set;
    int getSetElePos(int);
public:
    BinaryRelation(BooleanMatrix const &m, Set const &s);
    int inDegree(int);
    int outDegree(int);

    BinaryRelation pathOfLength(int);

    // Properties of Relations.    
    bool isReflexive() const;
    bool isIrreflexive() const;
    bool isSymmetric() const;
    bool isAsymmetric() const;
    bool isAntisymmetric() const;
    bool isTransitive() const;

    bool isEquivalence() const;
    
    BinaryRelation composition(const BinaryRelation &);

    BinaryRelation reflexiveClosure() const;
    BinaryRelation symmetricClosure() const;
    BinaryRelation transitiveClosure() const;
    
};

#endif
