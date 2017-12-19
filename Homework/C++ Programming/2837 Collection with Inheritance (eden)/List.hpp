// MegaShow
#ifndef LIST_HPP_
#define LIST_HPP_

#include "Collection.hpp"

class List : public Collection {
    public:
    virtual ~List() {}
    virtual E& operator[](int index) = 0;
    virtual E& get(int index) = 0;
    virtual int indexOf(E element) = 0;
    virtual void sort(void) = 0;
};

#endif
