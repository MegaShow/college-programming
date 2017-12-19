#include<iostream>
#include"source.h"
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        double x, y, z;
        cin >> x >> y >> z;
        base* b;
        circle* c = new circle(x);
        square* s = new square(x);
        rectangle* r = new rectangle(x, y);
        triangle* t = new triangle(x, y, z);
        b = c;
        cout << "circle area : " << b->area() << endl;
        b = s;
        cout << "square area : " << b->area() << endl;
        b = r;
        cout << "rectangle area : " << b->area() << endl;
        b = t;
        cout << "triangle area : " << b->area() << endl;
    }
}
