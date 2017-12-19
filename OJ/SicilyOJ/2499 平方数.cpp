/* 2499 平方数 */

#include <iostream>
#include <cstring>
using namespace std;

int arr[60001];

void GetNum(){
    for(int i = 0; i <= 60000; i++)
        arr[i] = 4;
    for(int i = 0; i * i <= 60000; i++)
        arr[i*i] = 1;
    for(int i = 1; i <= 60000; i++){
        if(arr[i] == 4){
            for(int j = 1; j * j <= i; j++){
                if(arr[i-j*j] == 1){
                    arr[i] = 2;
                    break;
                }
                else if(arr[i-j*j] == 2){
                    arr[i] = 3;
                }
            }
        }
    }
}

int main(){
    GetNum();
    int num, var;
    cin >> num;
    for(int i = 0; i < num; i++){
        cin >> var;
        cout << arr[var] << endl;
    }
    return 0;
}
