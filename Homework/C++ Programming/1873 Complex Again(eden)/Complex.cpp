// MegaShow
#include "Complex.hpp"

ostream & operator<<(ostream & out, const Complex & c){
	if(c.r == 0 && c.i == 0)
		out << 0;
	if(c.r != 0)
		out << c.r;
	if(c.i > 0)
		out << "+" << c.i << "i" << endl;
	else if(c.i < 0)
		out << c.i << "i" << endl;
	return out;
}

Complex::Complex(){
	r = i = 0;
}

Complex::Complex(const Complex & c){
	r = c.r;
	i = c.i;
}

Complex::Complex(double _r, double _i){
	r = _r;
	i = _i;
}

Complex Complex::operator+(const Complex & c){
	Complex tmp = c;
	tmp.r += r;
	tmp.i += i;
	return tmp;
}

Complex Complex::operator-(const Complex & c){
	Complex tmp = *this;
	tmp.r -= c.r;
	tmp.i -= c.i;
	return tmp;
}

Complex Complex::operator*(const Complex & c){
	Complex tmp;
	tmp.r = r * c.r - i * c.i;
	tmp.i = r * c.i + i * c.r;
	return tmp;
}

Complex Complex::operator/(const Complex & c){
	Complex tmp;
	tmp.r = (r * c.r + i * c.i) / (c.r * c.r + c.i * c.i);
	tmp.i = (i * c.r - r * c.i) / (c.r * c.r + c.i * c.i);
	return tmp;
}

Complex & Complex::operator+=(const Complex & c){
	*this = *this + c;
	return *this;
}

Complex & Complex::operator-=(const Complex & c){
	*this = *this - c;
	return *this;
}
Complex & Complex::operator*=(const Complex & c){
	*this = *this * c;
	return *this;
}

Complex & Complex::operator/=(const Complex & c){
	*this = *this / c;
	return *this;
}

bool Complex::operator==(const Complex & c){
	return r == c.r && i == c.i;
}

bool Complex::operator!=(const Complex & c){
	return !(*this == c);
}

void Complex::SetReal(double _r){
	r = _r;
}

void Complex::SetImag(double _i){
	i = _i;
}