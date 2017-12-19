// MegaShow
#include "stack.hpp"

stack::~stack() {
    delete [] storage;
}

void stack::push(E ele) {
    if (size == max_size) {
        return;
    }
    storage[size] = ele;
    size++;
}

void stack::pop() {
    if (size == 0) {
        return;
    }
    size--;
}

E stack::top() {
    if (size == 0) {
        return 0;
    }
    return storage[size-1];
}

bool stack::isEmpty() {
    return size == 0;
}

bool stack::isFull() {
    return size == max_size;
}

void stack::clear() {
    size = 0;
}