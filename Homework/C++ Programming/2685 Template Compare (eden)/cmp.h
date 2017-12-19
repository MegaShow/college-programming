// MegaShow
#include <string>
using namespace std;

template <class type>
bool cmp(type a, type b) {
    return a == b;
}

template <class type>
bool cmp(type* a, type* b) {
    return *a == *b;
}

bool cmp(char* a, char* b) {
    return string(a) == string(b);
}

