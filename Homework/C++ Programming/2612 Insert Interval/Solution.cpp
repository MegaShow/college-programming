// MegaShow
#include "Solution.hpp"

/*vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
    vector<Interval> tmp;
    bool flag = false;
    vector<Interval>::iterator it = intervals.begin();
    while (it != intervals.end()) {
        if (it->start < newInterval.end && flag == false) {
            tmp.push_back(newInterval);
            flag = true;
            it++;
        } else if (it->end < newInterval.start) {
            tmp.push_back(*it);
            it++;
        } else if (it->start > newInterval.start && it->end > newInterval.end) {
            Interval c(newInterval.start, it->end);
            tmp.push_back(c);
            it++;
        } else if (it->start < newInterval.start && it->end < newInterval.end) {
            Interval c(it->start, newInterval.end);
            it++;
            while (it != intervals.end()) {
                if (newInterval.end >= it->start && newInterval.end <= it->end) {
                    c.end = it->end;
                    it++;
                    break;
                } else if(newInterval.end < it->start) {
                    break;
                }
                it++;
            }
        } else {

        }
    }
    return tmp;
}*/

vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
    vector<Interval>::iterator it = intervals.begin();
    vector<Interval> tmp;
    if (newInterval.end < it->start) {
        tmp.push_back(newInterval);
    } else {
        while (it != intervals.end() && it->end < newInterval.start) {
            tmp.push_back(*it);
            it++;
        }
        if (it->end >= newInterval.start) {
            while (it != intervals.end() && newInterval.end >= it->start) {
                newInterval.end = (it->end > newInterval.end ? it->end : newInterval.end);
                newInterval.start = (it->start < newInterval.start ? it->start : newInterval.start);
                it++;
            }
            tmp.push_back(newInterval);
        }
    }
    while (it != intervals.end()) {
        tmp.push_back(*it);
        it++;
    }
    return tmp;
}

