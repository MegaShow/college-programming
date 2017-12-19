// MegaShow
#include <iostream>
#include "FUN.hpp"

FUN::FUN(char *s) {
    int i = 0;
    while(s[i])
        i++;
    str = new char[i+1];
    for(int j = 0; j <= i; j++)
        str[j] = s[j];
}

FUN::FUN(const FUN& c) {
    int i = 0;
    while(c.str[i])
        i++;
    str = new char[i+1];
    for(int j = 0; j <= i; j++)
        str[j] = c.str[j];
}

void FUN::show() {
    std::cout << str << std::endl;
}
