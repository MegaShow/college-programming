// MegaShow
#ifndef POINT_H_
#define POINT_H_

#include <iostream>
using namespace std;

class Point
{
private:
    int *data;
    int dimension;
public:
    Point(int d) {
        dimension = d;
        data = NULL;
    }

    Point(int* arr, int len) {
        dimension = len;
        data = new int [len];
        for (int i = 0; i < dimension; i++) {
            data[i] = arr[i];
        }
    }

    ~Point() {
        if (data != NULL) {
            delete [] data;
        }
    }

    Point operator+(const Point& p) {
        int len = (dimension>p.dimension?dimension:p.dimension);
        int slen = (dimension<p.dimension?dimension:p.dimension);
        Point tmp(len);
        tmp.data = new int [len];
        for (int i = 0; i < slen; i++) {
            tmp.data[i] = data[i] + p.data[i];
        }
        if (dimension > p.dimension) {
            for (int i = slen; i < len; i++) {
                tmp.data[i] = data[i];
            }
        } else if (dimension < p.dimension) {
            for (int i = slen; i < len; i++) {
                tmp.data[i] = p.data[i];
            }
        }
        return tmp;
    }

    Point operator-(const Point& p) {
        int len = (dimension>p.dimension?dimension:p.dimension);
        int slen = (dimension<p.dimension?dimension:p.dimension);
        Point tmp(len);
        tmp.data = new int [len];
        for (int i = 0; i < slen; i++) {
            tmp.data[i] = data[i] - p.data[i];
        }
        if (dimension > p.dimension) {
            for (int i = slen; i < len; i++) {
                tmp.data[i] = data[i];
            }
        } else if (dimension < p.dimension) {
            for (int i = slen; i < len; i++) {
                tmp.data[i] = -p.data[i];
            }
        }
        return tmp;
    }

    Point& operator=(const Point& p) {
        if (this == &p) {
            return *this;
        }
        delete [] data;
        dimension = p.dimension;
        data = new int [dimension];
        for (int i = 0; i < dimension; i++) {
            data[i] = p.data[i];
        }
    }

    void print() {
        cout << "(";
        for (int i = 0; i < dimension - 1; i++) {
            cout << data[i] << ",";
        }
        cout << data[dimension-1] << ")" << endl;
    }
};

#endif