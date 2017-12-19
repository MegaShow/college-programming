// MegaShow
#ifndef COMPLEX_HPP_
#define COMPLEX_HPP_

#include <iostream>
using namespace std;

//ostream & operator<<(ostream & out, const Complex & c);

class Complex{
private:
	double r;
	double i;
public:
	Complex();
	Complex(const Complex & c);
	Complex(double _r, double _i);
	Complex operator+(const Complex & c);
	Complex operator-(const Complex & c);
	Complex operator*(const Complex & c);
	Complex operator/(const Complex & c);
	Complex & operator+=(const Complex & c);
	Complex & operator-=(const Complex & c);
	Complex & operator*=(const Complex & c);
	Complex & operator/=(const Complex & c);
	bool operator==(const Complex & c);
	bool operator!=(const Complex & c);
	void SetReal(double _r);
    void SetImag(double _i);
	friend ostream & operator<<(ostream & out, const Complex & c);
};


#endif