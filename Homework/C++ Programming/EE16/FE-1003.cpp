/* EE 1003 */

#include <iostream>
using namespace std;

int main(){
    int n, m;
    cin >> n >> m;
    int arr[2][n+1];  // arr[0] next, arr[1] prev

    for(int i = 1; i < n; i++)
        arr[0][i] = i + 1;
    arr[0][n] = 1;
    for(int i = 2; i <= n; i++)
        arr[1][i] = i - 1;
    arr[1][1] = n;

    for(int i = 1, step = 1, out = 0; out < n; i = arr[0][i]){
        if(step == m){
            step = 1;
            out++;
            cout << i << endl;
            arr[0][ arr[1][i] ] = arr[0][i];
            arr[1][ arr[0][i] ] = arr[1][i];
        }
        else
            step++;
    }
    return 0;
}
