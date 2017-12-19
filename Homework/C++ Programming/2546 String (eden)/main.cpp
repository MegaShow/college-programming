#include <iostream>
#include "String.h"
using namespace std;
 int main() {
    char a[20];
    cin >> a;
    String s1(a);
    String s2 = s1;
    String s3(s1);
    cout << s1 << endl;
    cout << s2 << endl;
    cout << s3 << endl;
     cout << endl;
     s2[0] = '2';
    s3[0] = '3';
    cout << s1 << endl;
    cout << s2 << endl;
    cout << s3 << endl;
     cout << endl;
    char b[20];
    cin >> b;
    String s4(b);
    s3 = s4;
    cout << s3 << endl;
    cout << s4 << endl;
     return 0;
}
 