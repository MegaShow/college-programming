// 1002. Tiling a Grid With Dominoes
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int caseNum, val, odd = 0, even = 0;
    vector<int> v, res;
    cin >> caseNum;
    for (int i = 0; i < caseNum; i++) {
        cin >> val;
        v.push_back(val);
    }
    int maxVal = *max_element(v.begin(), v.end());
    res.push_back(1);
    res.push_back(1);
    for (int i = 2; i <= maxVal; i++) {
        even += res[i-2] * (i % 2 == 0 ? 3 : 2);
        odd += res[i-2] * (i % 2 != 0 ? 3 : 2);
        res.push_back(res[i-1] + res[i-2] + (i % 2 == 0 ? even : odd));
    }
    for (int i = 0; i < caseNum; i++) {
        cout << i + 1 << ' ' << res[v[i]] << endl;
    }
}
