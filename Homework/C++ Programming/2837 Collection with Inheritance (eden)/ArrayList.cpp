// MegaShow
#include <functional>
#include "ArrayList.hpp"

ArrayList::ArrayList() {
    _maxsize = extend_factor;
    storage = new E[_maxsize];
    _size = 0;
}

ArrayList::~ArrayList() {
    delete [] storage;
}

void ArrayList::add(E e) {
    if (_size == _maxsize) {
        extend();
    }
    storage[_size++] = e;
}

void ArrayList::clear(void) {
    _size = 0;
}

bool ArrayList::contain(E e) {
    for (int i = 0; i < _size; i++) {
        if (e == storage[i]) {
            return true;
        }
    }
    return false;
}

bool ArrayList::isEmpty(void) {
    return _size == 0;
}

void ArrayList::remove(E e) {
    E* data = new E[_maxsize];
    int k = 0;
    for (int i = 0; i < _size; i++) {
        if (e != storage[i]) {
            data[k++] = storage[i];
        }
    }
    delete [] storage;
    _size = k;
    storage = data;
}

E& ArrayList::operator[](int index) {
    return storage[index];
}

E& ArrayList::get(int index) {
    return storage[index];
}

int ArrayList::indexOf(E element) {
    for (int i = 0; i < _size; i++) {
        if (element == storage[i]) {
            return i;
        }
    }
    return -1;
}

void ArrayList::sort(void) {
    std::function<int(E*, int, int)> partition;
    partition = [](E* A, int lo, int hi)->int {
        E pivot = A[hi];
        int i = lo;
        for (int j = lo; j < hi; j++) {
            if (A[j] <= pivot) {
                E tmp = A[i];
                A[i] = A[j];
                A[j] = tmp;
                i++;
            }
        }
        A[hi] = A[i];
        A[i] = pivot;
        return i;
    };
    std::function<void(E*, int, int)> quicksort;
    quicksort = [&partition, &quicksort](E* A, int lo, int hi) {
        if (lo < hi) {
            int p = partition(A, lo, hi);
            quicksort(A, lo, p - 1);
            quicksort(A, p + 1, hi);
        }
    };
    quicksort(storage, 0, _size - 1);
}

int ArrayList::size(void) {
    return _size;
}

void ArrayList::extend(void) {
    _maxsize *= extend_factor;
    E* data = new E[_maxsize];
    for (int i = 0; i < _size; i++) {
        data[i] = storage[i];
    }
    delete [] storage;
    storage = data;
}
