#include "ListAdd.hpp"
using std::cout;
using std::endl;
using std::cin;
int main() {
    string s1, s2;
    // 0 < s1.length(),s2.length() <= 10000
    cout << "Input two Numbers" << endl;
    cin >> s1 >> s2;
    List l1(s1), l2(s2);
    List l3 = l1 + l2;
    cout << "After " << l1 << " + " << l2 <<endl;
    cout << l3 << endl << "Size : " << l3.size() << endl;
    List l4;
    l4 = l3 + l1;
    cout << "After " << l3 << " + " << l1 << endl;
    cout << l4 << endl << "Size : " << l4.size() << endl;
}