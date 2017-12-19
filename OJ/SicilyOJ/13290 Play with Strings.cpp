/* 13290 Play with Strings */

#include <iostream>
#include <cstring>
using namespace std;

int a[26], b[26];

int main(){
    bool flag;
    char str1[101], str2[101];
    cin >> str1 >> str2;
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    if(len1 != len2)
        cout << "NO" << endl;
    else{
        for(int i = 0; i < len1; i++)
            a[str1[i]-'a']++;
        for(int i = 0; i < len2; i++)
            b[str2[i]-'a']++;
        for(int i = 0; i < 26; i++){
            if(a[i] == b[i])
                flag = 1;
            else{
                flag = 0;
                cout << "NO" << endl;
                break;
            }
        }
        if(flag)
            cout << "YES" << endl;
    }
    return 0;
}
