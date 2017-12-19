#include <iostream>
#include "Matrix.h"
using namespace std;

int main() {
    int h1, w1, h2, w2, n;
    string name1 = "Mat1";
    string name2 = "Mat2";
    cin >> h1 >> w1;
    int **mat1_arr = new int*[h1];
    for (int i = 0; i < h1; i++) {
        mat1_arr[i] = new int[w1];
        for (int j = 0; j < w1; j++) {
            cin >> mat1_arr[i][j];
        }
    }
    cin >> h2 >> w2;
    int **mat2_arr = new int*[h2];
    for (int i = 0; i < h2; i++) {
        mat2_arr[i] = new int[w2];
        for (int j = 0; j < w2; j++) {
            cin >> mat2_arr[i][j];
        }
    }
    Matrix mat1 = Matrix(name1, h1, w1, mat1_arr);
    mat1.print();
    Matrix mat2 = Matrix(name2, h2, w2, mat2_arr);
    mat2.print();
    cout << "\n(Mat1 += Mat2) addition result:\n";
    mat1 += mat2;
    mat1.print();
    cout << "\n(Mat1 -= Mat2) substraction result:\n";
    mat1 -= mat2;
    mat1.print();
    cout << "\n(Mat1 * Mat2) production result:\n";
    Matrix mat3 = mat1 * mat2;
    if (mat3.getName() != "") mat3.print();
    for (int i = 0; i < h1; i++) {
        delete [] mat1_arr[i];
    }
    delete [] mat1_arr;
    for (int i = 0; i < h2; i++) {
        delete [] mat2_arr[i];
    }
    delete []mat2_arr;
    return 0;
}
