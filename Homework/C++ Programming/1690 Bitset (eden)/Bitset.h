#ifndef BITSET_H
#define BITSET_H
#include<iostream>
#define N 5
const int max_length = 32 * N;
class bitset {
    private:
        int a[N];
    public:
        bitset();
        void set(int pos);
        void reset(int pos);
        int count() const;
        bool test(int pos) const;
        bool any() const;
        bool none() const;
        bool all() const;
        bitset& operator&= (const bitset& b);
        bitset& operator|= (const bitset& b);
        bitset& operator^= (const bitset& b);
        bitset& operator= (const bitset& b);
        bitset& operator <<= (int pos);
        bitset& operator >>= (int pos);
        bitset operator~() const;
        bitset operator&(const bitset& b) const;
        bitset operator|(const bitset& b) const;
        bitset operator^(const bitset& b) const;
        bitset operator<<(int pos) const;
        bitset operator>>(int pos) const;
        bool operator== (const bitset& b) const;
        bool operator!= (const bitset& b) const;
        bool operator[] (int pos) const;
        friend std::ostream& operator << (std::ostream& os, const bitset& s) {
            for (int i = N-1; i >= 0; i--) {
                for (int j = 31; j >= 0; j--) {
                    if (s.a[i] & (1 << j)) os << 1;
                    else os << 0;
                }
            }
            return os;
        }
};
#endif
