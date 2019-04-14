#include <algorithm>
#include <iostream>
using namespace std;

int main() {
    int n;
    while (cin >> n) {
        int val[n];
        for (int i = 0; i < n; i++) {
            cin >> val[i];
        }
        sort(val, val + n);
        if (val[0] == val[n - 1]) {
          cout << n * (n - 1) / 2 << ' ' << n * (n - 1) / 2 << endl;
          continue;
        }
        int minVal = val[1] - val[0], minNum = 0;
        for (int i = 1; i < n; i++) {
            if (val[i] - val[i - 1] < minVal) {
                minVal = val[i] - val[i - 1];
            }
        }
        if (minVal != 0) {
            for (int i = 1; i < n; i++) {
                if (val[i] - val[i - 1] == minVal) {
                    minNum++;
                }
            }
        } else {
            for (int i = 1; i < n; i++) {
                for (int j = i - 1; j >= 0 && val[j] == val[i]; j--) {
                    minNum++;
                }
            }
        }
        int maxNum1 = 1, maxNum2 = 1;
        for (int i = 1; i < n && val[i] == val[i-1]; i++) {
            maxNum1++;
        }
        for (int i = n - 2; i >= 0 && val[i] == val[i+1]; i--) {
            maxNum2++;
        }
        cout << minNum << ' ' << maxNum1 * maxNum2 << endl;
    }

}
