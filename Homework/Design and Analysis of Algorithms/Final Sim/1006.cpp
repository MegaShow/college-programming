// 1006. Funny Game
#include <iostream>

using namespace std;

int main() {
    int a, b;
    while (cin >> a >> b && a != 0 && b != 0) {
        bool singa = true;
        int max = a > b ? a : b;
        int min = a > b ? b : a;
        while (min != 0) {
            if (max / min >= 2) {
                break;
            }
            int tmp = max - min;
            max = min;
            min = tmp;
            singa = !singa;
        }
        cout << (singa ? "Singa wins" : "Suny wins") << endl;
    }
}
