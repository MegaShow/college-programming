#include "Solution.hpp"
using std::cout;
using std::cin;
using std::endl;
int main() {
    int size;
    cin >> size;
    vector<Interval> intervals;
    int start, end;
    while (size--) {
        cin >> start >> end;
        Interval t(start, end);
        intervals.push_back(t);
    }
    cin >> start >>end;
    Interval newInterval(start, end);
    vector<Interval> res = insert(intervals, newInterval);
    for (int i = 0; i < res.size(); i++)
        cout << "[" << res[i].start << "," << res[i].end << "]" << endl;
}