/* EE 1006 关灯问题 */

#include <iostream>
using namespace std;

bool arr[101];

int main(){
    int n, m;
    cin >> n >> m;
    for(int i = 2; i <= m; i++){
        for(int k = i; k <= n; k++){
            if(k % i == 0)
                arr[k] = !arr[k];
        }
    }
    for(int i = 1; i <= n; i++){
        if(arr[i] == true)
            cout << "O";
        else
            cout << "#";
    }
    cout << endl;
    return 0;
}
