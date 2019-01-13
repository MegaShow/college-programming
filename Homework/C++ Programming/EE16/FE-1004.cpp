/* EE 1004 最简分数 */

#include <iostream>
#include <vector>
using namespace std;

int arr[100000][2];
int gcdvar[200][200];

int gcd(int a, int b){
    if(b == 0)
        return a;
    else{
        if(gcdvar[b][a%b] == 0)
            return gcd(b, a%b);
        else
            return gcdvar[b][a%b];
    }
}

int compare(int a[], int b[]){
    return a[0] * b[1] - a[1] * b[0];
}

int main(){
    int n, index = 0;
    cin >> n;
    for(int i = n; i > 0; i--){
        for(int j = 1; j < i; j++){
            gcdvar[i][j] = gcd(i,j);
            if(gcdvar[i][j] == 1){
                arr[index][0] = j;
                arr[index++][1] = i;
            }
        }
    }
    for(int i = index; i > 0; i--){
        for(int j = 0; j < i - 1; j++){
            if(compare(arr[j], arr[j+1]) > 0){
                swap(arr[j], arr[j+1]);
            }
        }
    }
    cout << "0/1" << endl;
    for(int i = 0; i < index; i++)
        cout << arr[i][0] << "/" << arr[i][1] << endl;
    cout << "1/1" << endl;
    return 0;
}
