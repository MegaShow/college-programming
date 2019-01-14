// 1003. Pair
// Solution 1 /0.88s
#include <algorithm>
#include <iostream>
#include <map>
#include <set>

using namespace std;

int main() {
    int caseNum, num, a, b;
    cin >> caseNum;
    for (int i = 0; i < caseNum; i++) {
        cin >> num;
        map<int, set<int>> m;
        map<int, int> count;
        for (int j = 1; j < num; j++) {
            cin >> a >> b;
            m[a].insert(b);
            m[b].insert(a);
            count[a]++;
            count[b]++;
        }
        if (num % 2 != 0) {
            cout << "No" << endl;
            continue;
        }
        bool flag = false; // 错误标记
        int del = 0; // 删除数量
        while (del != num) {
            auto del1 = find_if(next(count.begin(), 1), count.end(), [](const pair<int, int>& val) -> bool { return val.second == 1; });
            if (del1 == count.end()) {
                break;
            }
            auto del2 = find_if(m[del1->first].begin(), m[del1->first].end(), [&](const int& val) -> bool { return count[val] > 0; });
            if (del2 == m[del1->first].end()) {
                break;
            }
            count[del1->first] = 0;
            count[*del2] = 0;
            for (auto &item : m[*del2]) {
                count[item]--;
                if (count[item] == 0) {
                    flag = true;
                    break;
                }
            }
            if (flag) {
                break;
            }
            del += 2;
        }
        cout << (del == num ? "Yes" : "No") << endl;
    }
}

// Solution 2 /0.22s
#include <iostream>
#include <map>
#include <set>

using namespace std;

int main() {
    int caseNum, num, a, b;
    cin >> caseNum;
    for (int i = 0; i < caseNum; i++) {
        map<int, set<int>> m;
        cin >> num;
        for (int j = 1; j < num; j++) {
            cin >> a >> b;
            m[a].insert(b);
            m[b].insert(a);
        }
        if (num % 2 != 0) {
            cout << "No" << endl;
            continue;
        }
        bool flag = false; // 删除标记
        while (!flag) {
            flag = true;
            auto it = m.begin();
            while (it != m.end()) {
                if (it->second.size() == 1) {
                    for (auto &item : m[*it->second.begin()]) {
                        if (item != it->first) {
                            m[item].erase(*it->second.begin());
                        }
                    }
                    m.erase(*it->second.begin());
                    it = m.erase(it);
                    flag = false;
                } else {
                    it++;
                }
            }
        }
        cout << (m.size() == 0 ? "Yes" : "No") << endl;
    }
}
