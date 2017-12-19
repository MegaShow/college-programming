// MegaShow
#include <iomanip>
#include "Biginteger.h"

BigInteger::BigInteger(){
    size_ = 1;
    data_ = new int[size_];
    data_[0] = 0;
}

BigInteger::BigInteger(const string& number){
    size_ = number.length();
    data_ = new int[size_];
    for(int i = size_ - 1; i >= 0; i--)
        data_[size_ - 1 - i] = number[i] - '0';
}

BigInteger::BigInteger(const BigInteger& other){
    size_ = other.size_;
    data_ = new int[size_];
    for(int i = 0; i < size_; i++)
        data_[i] = other.data_[i];
}

BigInteger::~BigInteger(){
    delete [] data_;
}

BigInteger operator+(const BigInteger& left, const BigInteger& right){
    // create big and small obj
    BigInteger big = left.size_ >= right.size_ ? left : right;
    BigInteger small = left.size_ < right.size_ ? left : right;
    int big_size = big.size_ + 1;
    int* big_data = new int[big_size];
    for(int i = 0; i < big.size_; i++)
        big_data[i] = big.data_[i];
    big_data[big_size-1] = 0;
    delete [] big.data_;
    big.data_ = big_data;
    big.size_ = big_size;
    // add
    for(int i = 0, out = 0; i < big.size_; i++){
        if(i < small.size_)
            big.data_[i] = big.data_[i] + small.data_[i] + out;
        else
            big.data_[i] = big.data_[i] + out;
        out = big.data_[i] / 10;
        big.data_[i] %= 10;
    }
    return big;
}
 
// promise left >= right
BigInteger operator-(const BigInteger& left, const BigInteger& right){
    BigInteger tmp = left;
    for(int i = 0; i < tmp.size_; i++){
        if(i < right.size_)
            tmp.data_[i] -= right.data_[i];
        if(tmp.data_[i] < 0){
            tmp.data_[i] += 10;
            tmp.data_[i+1] -= 1;
        }
    }
    return tmp;
}

ostream& operator<<(ostream& out, const BigInteger& Bint){
    bool flag = false;
    for(int i = Bint.size_ - 1; i > 0; i--){
        if(flag || Bint.data_[i]){
            out << Bint.data_[i];
            flag = true;
        }
    }
    out << Bint.data_[0];
    return out;
}