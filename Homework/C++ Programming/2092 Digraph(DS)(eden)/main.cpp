//
//  main.cpp
//  C++
//
//  Created by 李天培 on 16/2/25.
//  Copyright © 2016年 lee. All rights reserved.
//

#include <iostream>

#include "Set.hpp"
#include "BooleanMatrix.hpp"
#include "Matrix.hpp"
#include "ProductSet.hpp"
#include "Digraph.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::string;

void displayProductSet(ProductSet temp) {
    int *a, *b;

    a = temp.getFirstSet().getMembers();
    b = temp.getSecondSet().getMembers();

    cout << "{";
    for (int i = 0; i < temp.getFirstSet().getSize(); i++) {
        for (int j = 0; j < temp.getSecondSet().getSize(); j++) {
            cout << ((i + j) != 0 ? "," : "")
            << "(" << a[i] << "," << b[j] << ")";
        }
    }
    cout << "}" << endl;
}

void displaySet(int* members, int size) {
    std::cout << "{";
    for (int i = 0; i < size; i++) {
        if (i < size - 1) std::cout << members[i] << ", ";
        else std::cout << members[i];
    }
    std::cout << "}" << std::endl;
}

void testBooleanMatrix() {
    cout << "TEST BOOLEAN MATRIX" << endl;

    int r = 0, c = 0;
    cin >> r >> c;
    BooleanMatrix m1(r, r);
    BooleanMatrix m2(r, r);
    BooleanMatrix m3(r, c);

    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= r; j++) {
            int t = 0;
            cin >> t;
            m1.replace(t, i, j);
        }
    }
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= r; j++) {
            int t = 0;
            cin >> t;
            m2.replace(t, i, j);
        }
    }

    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            int t = 0;
            cin >> t;
            m3.replace(t, i, j);
        }
    }

    m1.display();
    cout << endl;
    m2.display();
    cout << endl;
    m3.display();
    cout << endl;
    (m1 | m2).display();
    cout << endl;
    (m1 & m2).display();
    cout << endl;
    (m1.BooleanProduct(m3)).display();
}

void testDigraph() {
    cout << "TEST DIGRAPH" << endl;
    unsigned int r = 1;
    cin >> r;

    BooleanMatrix matrix(r, r);
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= r; j++) {
            bool t = true;
            int x;
            cin >> x;
            t = (x == 1) ? 1 : 0;
            matrix.replace(t, i, j);
        }
    }
    cout << "matrix:" << endl;
    matrix.display();
    cout << endl;

    Set set;
    int *test;
    test = new int[r];
    for (int i = 0; i < r; i++) {
        cin >> test[i];
        while (set.isInSet(test[i])) {
            test[i]++;
        }
        set.append(test[i]);
    }
    cout << "set:" << endl;
    displaySet(set.getMembers(), set.getSize());
    cout << endl;

    Digraph d(matrix, set);

    int x;
    cin >> x;
    cout << test[x] << "'s in degree: " << d.inDegree(test[x]) << endl;

    cin >> x;
    cout << test[x] << "'s out degree: " << d.outDegree(test[x]) << endl;

    cin >> x;
    Digraph pathD = d.pathOfLength(x);
    pathD.getBooleanMatrix().display();
    cout << endl;

    cout << "reflexvie: " << d.isReflexive() << endl;
    cout << "reflexvie: " << pathD.isReflexive() << endl;

    cout << "irreflexvie: " << d.isIrreflexive() << endl;
    cout << "irreflexvie: " << pathD.isIrreflexive() << endl;

    cout << "symmetric: " << d.isSymmetric() << endl;
    cout << "symmetric: " << pathD.isSymmetric() << endl;

    cout << "Asymmetric: " << d.isAsymmetric() << endl;
    cout << "Asymmetric: " << pathD.isAsymmetric() << endl;

    cout << "Antisymmetric: " << d.isAntisymmetric() << endl;
    cout << "Antisymmetric: " << pathD.isAntisymmetric() << endl;

    cout << "transitive: " << d.isTransitive() << endl;
    cout << "transitive: " << pathD.isTransitive() << endl;

    delete [] test;
}

void testProductSet() {
    cout << "test ProductSet" << endl;
    Set a;
    Set b;

    int n = 0;
    // number of set a
    cin >> n;
    for (int i = 0; i < n; i++) {
        int temp = 0;
        cin >> temp;
        a.append(temp);
    }

    // number of set b
    cin >> n;
    for (int i = 0; i < n; i++) {
        int temp = 0;
        cin >> temp;
        b.append(temp);
    }

    ProductSet test(a, b);
    displaySet(test.getFirstSet().getMembers(), test.getFirstSet().getSize());
    displaySet(test.getSecondSet().getMembers(), test.getSecondSet().getSize());

    displayProductSet(test);
}

int main() {
    testBooleanMatrix();
    testDigraph();
    testProductSet();
}
