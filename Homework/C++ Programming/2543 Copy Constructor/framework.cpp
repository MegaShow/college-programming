#include <iostream>
#include <cstring>
#include "FUN.hpp"
using namespace std;
int main()
{
    FUN a("Good luck!");
    FUN b(a);
    a.show();
    b.show();
    return 0;
}
