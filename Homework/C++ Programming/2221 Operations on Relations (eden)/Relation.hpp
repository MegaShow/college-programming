//
//  Relation.hpp
//  C++
//
//  Created by 李天培 on 16/4/9.
//  Copyright © 2016年 lee. All rights reserved.
//

#ifndef Relation_hpp
#define Relation_hpp

#include <iostream>
#include "BooleanMatrix.hpp"

class Relation {
protected:
    BooleanMatrix matrix;
public:
    Relation(BooleanMatrix const &);

    BooleanMatrix getBooleanMatrix() const;

    // Operations on Relations
    Relation complementary() const;
    Relation inverse() const;
    Relation operator&(const Relation &);
    Relation operator|(const Relation &);
};

#endif /* Relation_hpp */

