// MegaShow
// [03] Complex Number(Eden)
#include <iostream>
#include "Complex.hpp"


Complex::Complex(){
  setComplexNumber(0, 0);
}

Complex::Complex(double init_r, double init_i){
  setComplexNumber(init_r, init_i);
}

Complex Complex::add(Complex &right){
  Complex c(0, 0);
  c.setComplexNumber(r+right.get_r(), i+right.get_i());
  return c;
}

Complex Complex::subtract(Complex &right){
  Complex c(0, 0);
  c.setComplexNumber(r-right.get_r(), i-right.get_i());
  return c;
}

void Complex::printComplex() {
 std::cout << '(' << r << ", " << i << ')';
} // end function printComplex

void Complex::setComplexNumber( double rp, double ip ){
  r = rp;
  i = ip;
}

double Complex::get_r(){
  return r;
}

double Complex::get_i(){
  return i;
}
