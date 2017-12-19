// MegaShow
#ifndef SIMPLE_ITERATOR_H_
#define SIMPLE_ITERATOR_H_

class simple_iterator {
    private:
    char* pointer;

    public:
    simple_iterator() : pointer(0) {}
    simple_iterator(char* p) : pointer(p) {}

    char& base() {
        return *pointer;
    }

    char* prev() {
        return pointer - 1;
    }
    
    char* next() {
        return pointer + 1;
    }

    char* begin() {
        char* p = pointer;
        while (*p) {
            p--;
        }
        return p + 1;
    }

    char* end() {
        char* p = pointer;
        while (*p) {
            p++;
        }
        return p - 1;
    }

    char& operator*() {
        return *pointer;
    }

    simple_iterator operator++() {
        return (++pointer);
    }

    simple_iterator operator--() {
        return (--pointer);
    }

    simple_iterator operator++(int) {
        return pointer++;
    }

    simple_iterator operator--(int) {
        return pointer--;
    }

    simple_iterator operator+(int var) {
        return pointer + var;
    }

    simple_iterator operator-(int var) {
        return pointer - var;
    }

    bool operator<(const simple_iterator it) {
        return *pointer < *it.pointer;
    }

    bool operator>(const simple_iterator it) {
        return *pointer > *it.pointer;
    }

    bool operator<=(const simple_iterator it) {
        return *pointer <= *it.pointer;
    }

    bool operator>=(const simple_iterator it) {
        return *pointer >= *it.pointer;
    }
    
    bool operator==(const simple_iterator it) {
        return *pointer == *it.pointer; 
    }

    bool operator!=(const simple_iterator it) {
        return *pointer != *it.pointer;
    }
};

#endif
