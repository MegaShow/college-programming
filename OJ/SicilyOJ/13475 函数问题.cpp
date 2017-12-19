/* 13475 函数问题 */

int digit(int n,int k){
    int var;
    for(int i = 0; i < k; i++){
        var = n % 10;
        n /= 10;
    }
    return var;
}

/* test */
#include <iostream>
using namespace std;

int main(){
    cout << digit(15327, 4) << endl;
    return 0;
}
/* end of test */
