#ifndef __TYPES_HPP__
#define __TYPES_HPP__

#include <vector>

struct Facility {
    int capacity;
    int openingCost;
};

struct Customer {
    int demand;
    std::vector<int> assignmentCost;
};

struct Result {
    int cost;
    std::vector<bool> status;
    std::vector<size_t> assignment;
};

#endif // __TYPES_HPP__
