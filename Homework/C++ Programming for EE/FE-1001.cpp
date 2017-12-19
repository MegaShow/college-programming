/* EE 1001 剔除字符串 */

#include <iostream>
#include <cstring>
using namespace std;

int main(){
    char str1[101], str2[101];
    cin >> str1 >> str2;
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    for(int i = 0; i < len1; i++){
        for(int k = 0; k < len2; k++){
            if(str1[i] == str2[k]){
                str1[i] = 0;
                break;
            }
        }
    }
    for(int i = 0; i < len1; i++){
        if(str1[i] != 0)
            cout << str1[i];
    }
    cout << endl;
}
