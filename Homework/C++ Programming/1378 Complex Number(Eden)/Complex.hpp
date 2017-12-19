// Written by Matrix
#ifndef COMPLEX_HPP_
#define COMPLEX_HPP_

class Complex{
  private:
    double r;
    double i;
  public:
    Complex();
    Complex( double real, double imaginary );
    Complex add(Complex &right );
    Complex subtract(Complex &right );
    void printComplex();
    void setComplexNumber( double rp, double ip );
    double get_r();
    double get_i();
};

#endif
