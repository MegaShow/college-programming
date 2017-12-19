// MegaShow
#include "standard.hpp"

D::D(int a, int b, int c, int d, int e) : B(a, b), member(c, d) {
    k = e;
}

void D::print(void) const {
    cout << "Printing from Base:" << endl;
    B::print();
    cout << "Printing from member:" << endl;
    member.print();
    cout << "Printing from D field:" << endl;
    cout << k;
}