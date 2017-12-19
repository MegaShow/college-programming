#ifndef _SOLUTION_
#define _SOLUTION_

#include <vector>
#include <iostream>
using std::vector;
struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};

vector<Interval> insert(vector<Interval>& intervals, Interval newInterval);

#endif
