/* 2501 算算式 */

#include <iostream>
using namespace std;

#define MOD_VAR 9901

int main(){
    int n, k, sum = 0;
    cin >> n >> k;
    k %= (MOD_VAR - 1);
    for(int i = 0; i < k; i++)
        sum = (sum + 1) * n % MOD_VAR;
    cout << sum << endl;
    return 0;
}
