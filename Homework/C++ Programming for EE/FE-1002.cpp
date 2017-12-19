/* EE 1002 数列 */

#include <iostream>
#include <cmath>
using namespace std;

int arr[1010];

int main(){
    int k, n, arr_index = 1, index = 1;
    cin >> k >> n;
    arr[0] = 1;
    for(int i = 1; i < n; i = arr_index){
        arr[arr_index++] = pow(k, index++);
        for(int j = 0; j < i && arr_index < n; j++)
            arr[arr_index++] = arr[i] + arr[j];
    }
    cout << arr[n-1] << endl;
    return 0;
}
