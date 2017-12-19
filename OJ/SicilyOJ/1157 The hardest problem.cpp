// [1157]	The hardest problem

#include <iostream>
using namespace std;

int main() {
    int n,test,test_temp,i;
    part:cin >> n >> test_temp;
    if (n <= 0)
        return 0;
    i = 2;
    while (i <= n) {
        cin >> test;
        if (test > test_temp)
            test_temp = test;
        i += 1;
    }
    cout << test_temp << endl;
    goto part;
    return 0;
}      
