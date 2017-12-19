// [1293]	3n+1数链问题

#include <iostream>
using namespace std;

int main() {
    int i,j,var,num,var_temp,num_temp;
    cin >> i >> j;
    var_temp = var = i;
    num_temp = num = 1;
    while (var <= j) {
        while (var != 1) {
            if (var % 2 == 0)
                var /= 2;
            else
                var = var * 3 + 1;
            num += 1;
        }
        if (num > num_temp)
            num_temp = num;
        var = var_temp += 1;
        num = 1;
    }
}
