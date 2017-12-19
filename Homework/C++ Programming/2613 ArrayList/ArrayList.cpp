// MegaShow
#include "ArrayList.hpp"
 
ArrayList::ArrayList() {
    _size = 0;
    _maxsize = DEFAULT_MAX_SIZE;
    storage = new E [_maxsize];
}

ArrayList::~ArrayList() {
    if (storage != NULL) {
        delete [] storage;
    }
}

void ArrayList::add(E e) {
    if (_size == _maxsize) {
        extend();
    }
    storage[_size] = e;
    _size++;
}

void ArrayList::remove(E e) {
    int len = 0;
    int arr[_size];
    for (int i = 0; i < _size; i++) {
        if (storage[i] != e) {
            arr[len++] = storage[i];
        }
    }
    for (int i = 0; i < len; i++) {
        storage[i] = arr[i];
    }
    _size = len;
}

void ArrayList::clear() {
    _size = 0;
}

bool ArrayList::contain(E e) {
    for (int i = 0; i < _size; i++) {
        if (storage[i] == e) {
            return true;
        }
    }
    return false;
}

bool ArrayList::isEmpty() {
    return _size == 0;
}

E& ArrayList::operator[](int index) {
    return storage[index];
}

E& ArrayList::get(int index) {
    return storage[index];
}

int ArrayList::indexOf(E element) {
    for (int i = 0; i < _size; i++) {
        if (storage[i] == element) {
            return i;
        }
    }
    return -1;
}

int ArrayList::size() {
    return _size;
}

void ArrayList::extend() {
    _maxsize *= extend_factor;
    E* tmp = new E [_maxsize];
    for (int i = 0; i < _size; i++) {
        tmp[i] = storage[i];
    }
    delete [] storage;
    storage = tmp;
}
