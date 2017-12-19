// MegaShow
#ifndef COMPLEX_CPP_
#define COMPLEX_CPP_

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class Complex{
 private:
  double real;
  double imag;
 public:
  Complex(double x=0, double y=0) {
      real = x;
      imag = y;
  }

  friend ostream &operator <<(ostream& os, const Complex&c) {
      //e.g 2+3i  -2-5i
      string str;
      if (c.imag == 1) {
          str = "";
      } else if (c.imag == -1) {
          str = "-";
      } else {
          stringstream ss;
          ss << c.imag;
          ss >> str;
      }
      if(c.real == 0 && c.imag == 0) {
          os << 0;
      } else if (c.real == 0) {
          os << str << "i";
      } else if (c.imag == 0) {
          os << c.real;
      } else if (c.imag > 0) {
          os << c.real << "+" << str << "i";
      } else {
          os << c.real << str << "i";
      }
      return os;
  }
  
  friend istream &operator >>(istream& is, Complex &c) {
    is >> c.real >> c.imag;
    return is;
  }

  Complex operator +(const Complex &obj) {
      Complex tmp;
      tmp.real = real + obj.real;
      tmp.imag = imag + obj.imag;
      return tmp;
  }

  Complex operator -(const Complex &obj) {
      Complex tmp;
      tmp.real = real - obj.real;
      tmp.imag = imag - obj.imag;
      return tmp;
  }

  Complex operator *(const Complex &obj) {
      Complex tmp;
      tmp.real = real * obj.real - imag * obj.imag;
      tmp.imag = imag * obj.real + obj.imag * real;
      return tmp;
  }
};

#endif
