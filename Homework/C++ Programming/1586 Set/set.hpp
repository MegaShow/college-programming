//
//  Set.hpp
//  C++
//
//  Created by 李天培 on 16/2/25.
//  Copyright © 2016年 lee. All rights reserved.
//
 
#ifndef Set_hpp
#define Set_hpp
 
#include <stdio.h>
 
#define MAX_MEMBERS 100
 
class Set {
private:
    int members[MAX_MEMBERS];
    int size;
public:
    // Create an empty set.
    Set();
    // Create an set with some element.
    Set(int* m, int s);
    
    // append a element to set.
    // If element in the set, return false.
    // Or insert in set and return true.
    bool append(int e);
    
    // remove a element by its value from set.
    // If element in the set, then remove it and return true.
    // Or return false.
    bool remove(int e);
    
    // return true if the set is empty, or return false.
    bool isEmptySet();
    
    // return set.
    int* getMembers();
    
    // return size of set.
    int getSize();
 
    // return false if element not in the set, or return true.
    bool isInSet(int e);
    
};
 
#endif /* Set_hpp */