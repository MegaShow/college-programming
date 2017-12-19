//
//  ProductSet.hpp
//  C++
//
//  Created by 李天培 on 16/4/6.
//  Copyright © 2016年 lee. All rights reserved.
//

#ifndef ProductSet_hpp
#define ProductSet_hpp

#include <iostream>
#include "Set.hpp"

using std::cout;
using std::endl;

class ProductSet {
protected:
    Set first;
    Set second;
public:
    ProductSet(Set a, Set b);
    
    Set getFirstSet() const;
    Set getSecondSet() const;

    
};

#endif /* ProductSet_hpp */

