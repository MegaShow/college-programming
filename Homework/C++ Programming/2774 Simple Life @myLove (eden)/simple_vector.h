#ifndef SIMPLE_VECTOR_H
#define SIMPLE_VECTOR_H

#include <iostream>
#include <cstring>
#include "simple_iterator.h"
using namespace std;

static long long int MAX = 9999999;

class simple_vector {
    char* data;
    long long int size;
    long long int capacity;
  public:
    typedef simple_iterator iterator;

    simple_vector() : size(0), capacity(0) {
        data = new char[MAX];
        data[0] = '\0';
        memset(data, '\0', MAX);
    }

    ~simple_vector() {
        clear();
    }

    void clear() {
        delete [] data;
        size = capacity = 0;
    }

    long long int getSize() {
        return size;
    }

    long long int getCapacity() {
        return capacity;
    }

    void pushBack(char c) {
        if (capacity == 0)
            capacity = 1;
        else if (size == capacity)
            capacity = capacity * 2;
        data[++size] = c;
    }

    simple_iterator Begin() {
        return iterator(data + 1);
    }

    simple_iterator End() {
        return iterator((data + size + 1));
    }

    simple_iterator rBegin() {
        return iterator((data + size));
    }

    simple_iterator rEnd() {
        return iterator(data);
    }
};

#endif

