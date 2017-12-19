#include <iostream>
#include "test.h"
#include "base.h"
#include "vector.h"
 int main() {
    typedef myVector<int, testAllocator> v;
    Base * test = new v;
    delete static_cast<v *>(test);
    v * p1, * p2;
    int t;
     std::cout << "Test Constructor1:" << std::endl;
    p1 = new v;
    std::cout << "Size: " << p1->size() << std::endl;
    delete p1;
     std::cout << "Test Constructor2 and operator[]:" << std::endl;
    p1 = new v(static_cast<std::size_t>(6), 6);
    std::cout << "Size: " << p1->size() << std::endl;
    std::cout << "Content:";
    for (int i = 0; i < 2; ++i)
        std::cout << ' ' << (*p1)[i];
    std::cout << std::endl;
    std::cin >> t;
    std::cout << "Content after change:";
    (*p1)[0] = t;
    const v & r(*p1);
    for (int i = 0; i < 2; ++i)
        std::cout << ' ' << r[i];
    std::cout << std::endl;
     std::cout << "Test Constructor3 and iterators, including begin(), end():"
              << std::endl;
    p2 = new v(r.begin(), r.end());
    delete p1;
    std::cout << "Content:";
    for (v::iterator it = p2->begin(); it != p2->end(); ++it)
        std::cout << ' ' << *it;
    std::cout << std::endl;
     std::cout << "Test Constructor4:" << std::endl;
    *(p2->begin()) = 0;
    p1 = new v(*p2);
    delete p2;
    std::cout << "Content:";
    for (std::size_t i = 0; i < p1->size(); ++i)
        std::cout << ' ' << (*p1)[i];
    std::cout << std::endl;
     std::cout << "Test operator=:" << std::endl;
    p2 = new v(static_cast<std::size_t>(8), 8);
    *p2 = *p1;
    *p2 = *p2;
    delete p1;
    std::cout << "Content:";
    for (std::size_t i = 0; i < p2->size(); ++i)
        std::cout << ' ' << (*p2)[i];
    std::cout << std::endl;
     std::cout << "Test resize1:" << std::endl;
    p2->resize(2);
    std::cout << "Content:";
    for (std::size_t i = 0; i < p2->size(); ++i)
        std::cout << ' ' << (*p2)[i];
    std::cout << std::endl;
     std::cout << "Test resize2:" << std::endl;
    p2->resize(8, 8);
    std::cout << "Content:";
    for (std::size_t i = 0; i < p2->size(); ++i)
        std::cout << ' ' << (*p2)[i];
    std::cout << std::endl;
     std::cout << "Test reserve and capacity:" << std::endl;
    p2->reserve(33);
    std::cout << "Capacity: " << p2->capacity() << std::endl
              << "Size: " << p2->size() << std::endl;
    p2->reserve(2);
    std::cout << "Capacity: " << p2->capacity() << std::endl
              << "Size: " << p2->size() << std::endl;
     std::cout << "Test clear and empty:" << std::endl;
    if (p2->empty())
        std::cout << "True" << std::endl;
    else
        std::cout << "False" << std::endl;
    p2->clear();
    if (p2->empty())
        std::cout << "True" << std::endl;
    else
        std::cout << "False" << std::endl;
    std::cout << "Capcaity: " << p2->capacity() << std::endl
              << "Size: " << p2->size() << std::endl;
     int * arr = new int[5];
    for (int i = 0; i < 5; ++i)
        arr[i] = i+1;
    std::cout << "Test assign:" << std::endl;
    p2->assign(arr, arr+5);
    std::cout << "Content:";
    for (v::const_iterator it = p2->begin(); it != p2->end(); ++it)
        std::cout << ' ' << *it;
    std::cout << std::endl << "Size: " << p2->size()
              << std::endl << "Capacity: " << p2->capacity()
              << std::endl;
     delete [] arr;
    delete p2;
    return 0;
}
 