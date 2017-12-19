// [1001] Alphacode

#include <iostream>
#include <string>
using namespace std;

int main() {
	string s;
	while (cin >> s&&s != "0") {
		int a, b = 1, c = 1;
		for (int i = 1; i < s.length(); i++) {
			a = b; b = c; c = 0;
			if (s[i - 1] == '1' || (s[i - 1] == '2'&&s[i] <= '6'))c += a;
			if (s[i] >= '1'&&s[i] <= '9')c += b;
		}
		cout << c << endl;
	}
	return 0;
}

