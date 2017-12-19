#include <iostream>
#include "simple_vector.h"
using namespace std;

void test_iterator() {
    int t, i;
    char c;
    simple_vector ivec;
    simple_vector::iterator iter, iter1, iter2;

    cin >> t;
    for (i = 0; i < t; i++) {
        cin >> c;
        ivec.pushBack(c);
    }

    cout << "Foward test: ";
    for (iter = ivec.Begin(); iter != ivec.End(); ++iter)
        cout << *iter;
    cout << "\n";
    cout << "Backward test: ";
    for (iter = ivec.rBegin(); iter != ivec.rEnd(); --iter)
        cout << *iter;
    cout << "\n";

    cout << "Self-Foward test: ";
    iter1 = ivec.Begin();
    iter2 = ++iter1;
    cout << *iter2;
    iter1 = ivec.Begin();
    iter2 = iter1++;
    cout << *iter2 << "\n";

    cout << "Self-Backward test: ";
    iter1 = ivec.rBegin();
    iter2 = --iter1;
    cout << *iter2;
    iter1 = ivec.rBegin();
    iter2 = iter1--;
    cout << *iter2 << "\n";

    cout << "Compare test#1: ";
    iter1 = ivec.Begin();
    iter2 = ivec.rBegin();
    cout << (iter1 < iter2);
    cout << (iter1 > iter2);
    cout << (iter1 <= iter2);
    cout << (iter1 >= iter2);
    cout << (iter1 == iter1);
    cout << (iter1 != iter2) << "\n";

    cout << "Compare test#2: ";
    iter1 = ivec.Begin();
    iter2 = ivec.rBegin();
    cout << (iter2 < iter1);
    cout << (iter2 > iter1);
    cout << (iter1 <= iter1);
    cout << (iter2 >= iter2);
    cout << (iter1 == iter2);
    cout << (iter1 != iter1) << "\n";

    cout << "Move test: ";
    iter1 = ivec.Begin();
    iter2 = iter1 + 4;
    cout << *iter2;
    iter2 = iter2 - 3;
    cout << *iter2;
    iter2 = iter2 + 2;
    cout << *iter2 << "\n";

    cout << "C++11 test: ";
    iter1 = ivec.Begin();
    iter2 = ivec.rBegin();
    ++iter1;
    cout << *(iter1.begin());
    cout << *(iter1.end());
    cout << *(iter1.prev());
    cout << *(iter1.next());
    --iter2;
    cout << *(iter2.begin());
    cout << *(iter2.end());
    cout << *(iter2.prev());
    cout << *(iter2.next());
}

int main() {
    test_iterator();
    return 0;
}

