/* 1001 Complex Number */

#include <cmath>

class ComplexNum{
private:
	double rpart;
	double ipart;
public:
	// Constructed Function
	ComplexNum();
	ComplexNum(double initr, double initi);
	// Get Message
	double GetRealPart();
	double GetImaginaryPart();
	double GetModulus();
	// Operating
	void add(ComplexNum c);
	void subtract(ComplexNum c);
	void multiply(ComplexNum t);
	void divide(ComplexNum t);
	// Update Message
	void SetRealPart(double r);
	void SetImaginaryPart(double i);
};

ComplexNum::ComplexNum(){ rpart = ipart = 0; }
ComplexNum::ComplexNum(double initr, double initi){
	rpart = initr;
	ipart = initi;
}

double ComplexNum::GetRealPart(){ return rpart; }
double ComplexNum::GetImaginaryPart(){ return ipart; }

void ComplexNum::add(ComplexNum c){
	rpart += c.GetRealPart();
	ipart += c.GetImaginaryPart();
}

void ComplexNum::subtract(ComplexNum c){
	rpart -= c.GetRealPart();
	ipart -= c.GetImaginaryPart();
}

void ComplexNum::multiply(ComplexNum t){
	double a = rpart;
	double b = ipart;
	double c = t.GetRealPart();
	double d = t.GetImaginaryPart();
	rpart = a * c - b * d;
	ipart = a * d + b * c;
}

void ComplexNum::divide(ComplexNum t){
	double a = rpart;
	double b = ipart;
	double c = t.GetRealPart();
	double d = t.GetImaginaryPart();
	rpart = (a * c + b * d) / (c * c + d * d);
	ipart = (b * c - a * d) / (c * c + d * d);
}

void ComplexNum::SetRealPart(double r){ rpart = r; }
void ComplexNum::SetImaginaryPart(double i){ ipart = i; }

double ComplexNum::GetModulus(){
	return sqrt(rpart * rpart + ipart * ipart);
}