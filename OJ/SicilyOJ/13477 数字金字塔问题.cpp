/* 13477 数字金字塔问题 */

#include <iostream>
using namespace std;

int main(){
    int var;
    cin >> var;
    for(int i = 1; i <= var; i++){
        for(int j = 1; j < i; j++)
            cout << j << " ";
        for(int j = i; j > 1; j--)
            cout << j << " ";
        cout << 1 << endl;
    }
    return 0;
}
