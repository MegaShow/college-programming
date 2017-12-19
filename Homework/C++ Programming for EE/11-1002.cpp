/* 1002 Phone Number */

enum Type{
	HOME,
	OFFICE,
	FAX,
	CELL,
	PAGER
};

class PhoneNum{
private:
	int countryCode;
	int areaCode;
	int number;
	Type type;
public:
	// Constructed Function
	PhoneNum();
	PhoneNum(int cCode, int aCode, int num, Type t);
	PhoneNum(int num, Type t);
	// Get Message
	int GetCountryCode();
	int GetAreaCode();
	int GetPhoneNum();
	Type GetType();
	// Update Message
	void SetCountryCode(int cCode);
	void SetAreaCode(int aCode);
	void SetPhoneNum(int num);
	void SetType(Type t);
	// Comparison
	bool Equal(PhoneNum c);
};


PhoneNum::PhoneNum(){
	countryCode = 0;
	areaCode = 0;
	number = 0;
	type = HOME;
}

PhoneNum::PhoneNum(int cCode, int aCode, int num, Type t){
	countryCode = cCode;
	areaCode = aCode;
	number = num;
	type = t;
}

PhoneNum::PhoneNum(int num, Type t){
	countryCode = 86;
	areaCode = 20;
	number = num;
	type = t;
}

int PhoneNum::GetCountryCode(){ return countryCode; }
int PhoneNum::GetAreaCode(){ return areaCode; }
int PhoneNum::GetPhoneNum(){ return number; }
Type PhoneNum::GetType(){ return type; }

void PhoneNum::SetCountryCode(int cCode){ countryCode = cCode; }
void PhoneNum::SetAreaCode(int aCode){ areaCode = aCode; }
void PhoneNum::SetPhoneNum(int num){ number = num; }
void PhoneNum::SetType(Type t){ type = t; }

bool PhoneNum::Equal(PhoneNum c){
	if(number == c.GetPhoneNum())
		return true;
	return false;
}