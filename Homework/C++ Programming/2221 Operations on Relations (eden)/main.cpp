//
//  main.cpp
//  C++
//
//  Created by 李天培 on 16/2/25.
//  Copyright © 2016年 lee. All rights reserved.
//

#include "Set.hpp"
#include "BooleanMatrix.hpp"
#include "Matrix.hpp"
#include "BinaryRelation.hpp"
#include "Relation.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::string;

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
    cout << "TEST BinaryRelation" << endl;
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

    BinaryRelation d(matrix, set);

    int x;
    cin >> x;
    cout << test[x] << "'s in degree: " << d.inDegree(test[x]) << endl;

    cin >> x;
    cout << test[x] << "'s out degree: " << d.outDegree(test[x]) << endl;

    cin >> x;
    BinaryRelation pathD = d.pathOfLength(x);
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

    cout << "Equivalence: " << d.isEquivalence() << endl;
    cout << "Equivalence: " << pathD.isEquivalence() << endl;

    cout << "reflexive closure: " << endl;
    d.reflexiveClosure().getBooleanMatrix().display();
    cout << "reflexvie: " << d.reflexiveClosure().isReflexive() << endl;

    cout << "symmetric closure: " << endl;
    d.symmetricClosure().getBooleanMatrix().display();
    cout << "symmetric: " << d.symmetricClosure().isSymmetric() << endl;

    cout << "transitive closure: " << endl;
    d.transitiveClosure().getBooleanMatrix().display();
    cout << "transitive: " << d.transitiveClosure().isTransitive() << endl;

    cout << "composition: " << endl;
    d.composition(pathD).getBooleanMatrix().display();


    delete [] test;
}



void testRelation() {
    cout << "test relation" << endl;
    unsigned int r = 1, c = 1;
    cin >> r >> c;

    BooleanMatrix matrix1(r, c);
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            bool t = true;
            int x;
            cin >> x;
            t = (x == 1) ? 1 : 0;
            matrix1.replace(t, i, j);
        }
    }
    cout << "matrix1:" << endl;
    matrix1.display();
    cout << endl;

    BooleanMatrix matrix2(r, c);
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            bool t = true;
            int x;
            cin >> x;
            t = (x == 1) ? 1 : 0;
            matrix2.replace(t, i, j);
        }
    }
    cout << "matrix2:" << endl;
    matrix2.display();
    cout << endl;

    Relation r1(matrix1);
    r1.getBooleanMatrix().display();
    cout << endl;

    Relation r2(matrix2);
    r2.getBooleanMatrix().display();
    cout << endl;

    r1.complementary().getBooleanMatrix().display();
    cout << endl;
    r1.inverse().getBooleanMatrix().display();
    cout << endl;

    (r1 & r2).getBooleanMatrix().display();
    cout << endl;
    (r1 | r2).getBooleanMatrix().display();
    cout << endl;
}

int main() {
    testBooleanMatrix();
    testDigraph();
    testRelation();
}


