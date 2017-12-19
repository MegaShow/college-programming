// MegaShow

#ifndef FACTORY_HPP_
#define FACTORY_HPP_

#include "Product.hpp"

class Factory {
public:
    virtual Laptop* produceLaptop() = 0;
    virtual MobilePhone* produceMobilePhone() = 0;
    virtual ~Factory() {}
};


class AppleFactory : public Factory {
public:
    virtual Laptop* produceLaptop() {
        Laptop* pr = new AppleLaptop();
        return pr;
    }

    virtual MobilePhone* produceMobilePhone() {
        MobilePhone* pr = new AppleMobilePhone();
        return pr;
    }

    virtual ~AppleFactory() {}
};


class XiaomiFactory : public Factory {
public:
    virtual Laptop* produceLaptop() {
        Laptop* pr = new XiaomiLaptop();
        return pr;
    }

    virtual MobilePhone* produceMobilePhone() {
        MobilePhone* pr = new XiaomiMobilePhone();
        return pr;
    }

    virtual ~XiaomiFactory() {}
};

#endif
