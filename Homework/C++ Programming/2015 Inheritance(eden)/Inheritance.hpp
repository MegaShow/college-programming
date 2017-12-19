// MegaShow
#ifndef INHERITANCE_HPP_
#define INHERITANCE_HPP_

#include <iostream>
using std::cout;
using std::endl;

class baseA{
public:
	baseA();
	~baseA();
};

class baseB{
public:
	baseB();
	~baseB();
};

class derivedA : public baseA{
public:
	derivedA();
	~derivedA();
};

class derivedB : public baseA, public baseB{
public:
	derivedB();
	~derivedB();
};

class C : public derivedA, public derivedB{
public:
	C();
	~C();
};


#endif