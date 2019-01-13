// 4868. 数字反转
#include <iostream>

using namespace std;

int main() {
    int val, res = 0;
    cin >> val;
    while (val) {
        res = res * 10 + val % 10;
        val = val / 10;
    }
    cout << res << endl;
}
