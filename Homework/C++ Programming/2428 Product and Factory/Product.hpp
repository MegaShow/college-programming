// MegaShow

#ifndef PRODUCT_HPP_
#define PRODUCT_HPP_

#include <iostream>

class Laptop {
public:
    virtual void compileCppProgram() = 0;
    virtual ~Laptop() {}
};

class AppleLaptop : public Laptop {
public:
    virtual void compileCppProgram() {
        std::cout << "Apple Laptop compiles a cpp program." << std::endl;
    }

    virtual ~AppleLaptop() {}
};

class XiaomiLaptop : public Laptop {
public:
    virtual void compileCppProgram() {
        std::cout << "Xiaomi Laptop compiles a cpp program." << std::endl;
    }

    virtual ~XiaomiLaptop() {}
};



class MobilePhone {
public:
    virtual void sendShortMessage() = 0;
    virtual ~MobilePhone() {}
};

class AppleMobilePhone : public MobilePhone {
public:
    virtual void sendShortMessage() {
        std::cout << "Apple MobilePhone sends a short message." << std::endl;
    }

    virtual ~AppleMobilePhone() {}
};

class XiaomiMobilePhone : public MobilePhone {
public:
    virtual void sendShortMessage() {
        std::cout << "Xiaomi MobilePhone sends a short message." << std::endl;
    }

    virtual ~XiaomiMobilePhone() {}
};

#endif
