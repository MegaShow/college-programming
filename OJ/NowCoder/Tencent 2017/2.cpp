#include <cstring>
#include <iostream>
using namespace std;

int main() {
    char s[1001];
    while (cin >> s) {
        int len = strlen(s);
        int end = len, i = 0;
        while (i < end) {
            if (s[i] >= 'A' && s[i] <= 'Z') {
                char c = s[i];
                for (int j = i; j < len - 1; j++) {
                    s[j] = s[j + 1];
                }
                s[len - 1] = c;
                end--;
            } else {
                i++;
            }
        }
        cout << s << endl;
    }
}
