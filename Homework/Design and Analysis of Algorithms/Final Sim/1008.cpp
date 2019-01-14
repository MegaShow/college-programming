// 1008. Threecolor problem
#include <iostream>
#include <string>

using namespace std;

int main() {
    int caseNum, n, m;
    string str;
    cin >> caseNum;
    while (caseNum--) {
        cin >> n >> m >> str;
        int red = 0, yellow = 0, blue = 0;
        for (auto c : str) {
            switch (c) {
                case 'r': red++; break;
                case 'y': yellow++; break;
                case 'b': blue++; break;
            }
        }
        if (m <= red) {
            cout << 'r' << endl;
        } else if (m <= red + yellow) {
            cout << 'y' << endl;
        } else if (m <= red + yellow + blue) {
            cout << 'b' << endl;
        }
    }
}
