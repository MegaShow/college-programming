#include <iostream>
#include "Complex.hpp"
using namespace std;
int main(int argc, const char *argv[]) {
    double x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    // x1 and x2 are the real part, y1 and y2 are the imaginary part
    Complex a(x1, y1), b(x2, y2);
 
    Complex c = a;
    double c1, c2;
    // c1 is the real part and c2 is the imaginary part
    cin >> c1 >> c2;
 
    c.SetReal(c1);
    c.SetImag(c2);
 
    cout << c << endl;
    cout << a << endl;
 
    c = b;
    cout << c << endl;
 
    // a and b are not changed.
    cout << (a + b) << endl;
    cout << (a - b) << endl;
    cout << (a * b) << endl;
    cout << (a / b) << endl;
 
    a += b;
    cout << a << endl;
    a -= b;
    cout << a << endl;
    a *= b;
    cout << a << endl;
    a /= b;
    cout << a << endl;
 
    cout << (a == a) << endl;
    cout << (a != a) << endl;
 
    return 0;
}