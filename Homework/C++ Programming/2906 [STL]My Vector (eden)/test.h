#ifndef __TEST_H__
#define __TEST_H__
 #include <memory>
#include <iostream>
 class testAllocator : public std::allocator<int> {
    public:
        typedef std::allocator<int> Base;
        int * allocate(std::size_t size) {
            std::cout << "Test Allocator: allocate" << std::endl;
            return Base::allocate(size);
        }
        void deallocate(int * p, std::size_t size) {
            std::cout << "Test Allocator: deallocate" << std::endl;
            Base::deallocate(p, size);
        }
        void construct(int * p, int val) {
            std::cout << "Test Allocator: Construct, value: " << val
                      << std::endl;
            Base::construct(p, val);
        }
        void destroy(int * p) {
            std::cout << "Test Allocator: Destroy, value: " << *p << std::endl;
            Base::destroy(p);
        }
};
 #endif
 