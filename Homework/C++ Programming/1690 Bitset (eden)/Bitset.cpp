// MegaShow
#include "Bitset.h"

bitset::bitset(){
    for(int i = 0; i < N; i++)
        a[i] = 0;
}

void bitset::set(int pos){
    a[pos/32] |= (1 << (pos % 32));
}

void bitset::reset(int pos){
    a[pos/32] &= ~(1 << (pos % 32));
}

int bitset::count() const{
    int counter = 0;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < 32; j++){
            if(a[i] & (1 << j))
                counter++;
        }
    }
    return counter;
}

bool bitset::test(int pos) const{
    return (a[pos/32] >> (pos % 32)) & 1;
}

bool bitset::any() const{
    for(int i = 0; i < N * 32; i++){
        if(test(i))
            return true;
    }
    return false;
}

bool bitset::none() const{
    return !any();
}

bool bitset::all() const{
    for(int i = 0; i < N * 32; i++){
        if(test(i) == false)
            return false;
    }
    return true;
}

bitset &bitset::operator&=(const bitset &b){
    *this = *this & b;
    return *this;
}

bitset &bitset::operator|=(const bitset &b){
    *this = *this | b;
    return *this;
}

bitset &bitset::operator^=(const bitset &b){
    *this = *this ^ b;
    return *this;
}

bitset &bitset::operator=(const bitset &b){
    for(int i = 0; i < N; i++)
        a[i] = b.a[i];
    return *this;
}

bitset &bitset::operator<<=(int pos){
    *this = *this << pos;
    return *this;
}

bitset &bitset::operator>>=(int pos){
    *this = *this >> pos;
    return *this;
}

bitset bitset::operator~() const{
    bitset tmp;
    for(int i = 0; i < N * 32; i++){
        if(test(i))
            tmp.reset(i);
        else
            tmp.set(i);
    }
    return tmp;
}

bitset bitset::operator&(const bitset &b) const{
    bitset tmp;
    for(int i = 0; i < N; i++)
        tmp.a[i] = (a[i] & b.a[i]);
    return tmp;
}

bitset bitset::operator|(const bitset &b) const{
    bitset tmp;
    for(int i = 0; i < N; i++)
        tmp.a[i] = (a[i] | b.a[i]);
    return tmp;
}

bitset bitset::operator^(const bitset &b) const{
    bitset tmp;
    for(int i = 0; i < N; i++)
        tmp.a[i] = (a[i] ^ b.a[i]);
    return tmp;
}

bitset bitset::operator<<(int pos) const{
    bitset tmp;
    for(int i = N * 32 - pos - 1; i >= 0; i--){
        if(test(i))
            tmp.set(i+pos);
        else
            tmp.reset(i+pos);
    }
    for(int i = 0; i < pos; i++)
        tmp.reset(i);
    return tmp;
}

bitset bitset::operator>>(int pos) const{
    bool flag = test(N*32-1);
    bitset tmp;
    for(int i = pos; i < N * 32; i++){
        if(test(i))
            tmp.set(i-pos);
        else
            tmp.reset(i-pos);
    }
    for(int i = N * 32 - pos; i < N * 32; i++)
        flag ? tmp.set(i) : tmp.reset(i);
    return tmp;
}

bool bitset::operator==(const bitset &b) const{
    for(int i = 0; i < N * 32; i++){
        if(test(i) != b.test(i))
            return false;
    }
    return true;
}

bool bitset::operator!=(const bitset &b) const{
    return !((*this) == b);
}

bool bitset::operator[](int pos) const{
    return test(pos);
}