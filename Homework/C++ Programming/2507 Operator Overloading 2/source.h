 // MegaShow
#include <iostream>

class Calculator {
private:
    int value;
public:
    Calculator(int value_) : value(value_) {}
    int operator++() {
        value++;
        if(value == 100)
            value = 0;
        std::cout << "counter = " << value << std::endl;
        return value;
    }

    int operator--() {
        value--;
        if(value == -1)
            value = 0;
        std::cout << "counter = " << value << std::endl;
        return value;
    }
};
