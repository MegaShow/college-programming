// [1798] Alice and Bob

#include <iostream>
using namespace std;

int main() {
    short n;
    cin >> n;
    while (n != 0) {
        cout << (n % 2 == 0 ? "Alice" : "Bob") << endl;
        cin >> n;
    }
    return 0;
}                   
