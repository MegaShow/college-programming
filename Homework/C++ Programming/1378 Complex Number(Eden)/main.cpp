// Written by Matrix
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include "Complex.hpp"

int main() {
    int n[8];
    cin >> n[0] >> n[1] >> n[2] >> n[3];
    cin >> n[4] >> n[5] >> n[6] >> n[7];
    Complex a(n[0], n[1]), b(n[2], n[3]), c;
    // create three Complex objects

    a.printComplex();  // output object a
    cout << " + ";
    b.printComplex();  // output object b
    cout << " = ";
    c = a.add(b);
    // invoke add function and assign to object c
    c.printComplex();  // output object c

    cout << '\n';
    a.setComplexNumber(n[4], n[5]);  // reset realPart and
    b.setComplexNumber(n[6], n[7]);  // and imaginaryPart
    a.printComplex();  // output object a
    cout << " - ";
    b.printComplex();  // output object b
    cout << " = ";
    c = a.subtract(b);  // invoke add function and assign to object c
    c.printComplex();  // output object c
    cout << endl;
}  // end main
 
