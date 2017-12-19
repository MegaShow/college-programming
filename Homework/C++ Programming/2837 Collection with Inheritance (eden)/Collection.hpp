// MegaShow
#ifndef COLLECTION_HPP_
#define COLLECTION_HPP_

typedef int E;

class Collection {
    public:
    virtual ~Collection() {}
    virtual void add(E e) = 0;
    virtual void clear(void) = 0;
    virtual bool contain(E e) = 0;
    virtual bool isEmpty(void) = 0;
    virtual void remove(E e) = 0;
    virtual int size(void) = 0;
};

#endif
