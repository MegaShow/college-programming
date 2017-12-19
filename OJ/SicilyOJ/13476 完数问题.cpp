/* 13476 完数问题 */

#include <iostream>
using namespace std;

void GetNumber(int var){
    for(int i = 2; i <= var; i++){
        int sum = 0;
        int k = i / 2;
        for(int j = 1; j <= k; j++){
            if(i % j == 0)
                sum += j;
        }
        if(sum == i)
            cout << i << endl;
    }
}

int main(){
    int var;
    cin >> var;
    GetNumber(var);
}
