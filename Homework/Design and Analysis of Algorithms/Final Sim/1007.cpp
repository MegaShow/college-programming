// 1007. Greatest Common Divisors
#include <iostream>

using namespace std;

int gcd(int a, int b) {
    if (a % b == 0) {
        return b;
    }
    return gcd(b, a % b);
}

int main() {
    int caseNum, a, b, min, max;
    cin >> caseNum;
    while (caseNum--) {
        cin >> a >> b >> min >> max;
        int val = gcd(a, b);
        if (val >= min && val <= max) {
            cout << val << endl;
        } else {
            for (int i = max; i >= min; i--) {
                if (val % i == 0) {
                    val = i;
                    break;
                }
            }
            if (val >= min && val <= max) {
                cout << val << endl;
            } else {
                cout << "No answer" << endl;
            }
        }
    }
}
