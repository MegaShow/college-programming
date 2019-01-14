// 1005. Prime Palindromes
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

bool checkPrime(int val) {
    if (val < 2 || (!(val & 1) && val != 2)) {
        return false;
    }
    for (int i = 3; i * i <= val; i += 2) {
        if (val % i == 0) {
            return false;
        }
    }
    return true;
}

void getTable(vector<int> &v) {
    v.push_back(11);
    for (int i = 5; i <= 10000; i++) {
        int val = i;
        for (int j = i / 10; j; j /= 10) {
            val = val * 10 + j % 10;
        }
        if (checkPrime(val)) {
            v.push_back(val);
        }
    }
    sort(v.begin(), v.end());
}

int main() {
    int a, b;
    vector<int> v;
    getTable(v);
    while (cin >> a >> b && (a != 0 || b != 0)) {
        for (auto &i : v) {
            if (i >= a && i <= b) {
                cout << i << endl;
            } else if (i > b) {
                break;
            }
        }
    }
}
