// UVA401 MegaShow 2017.1.25

#include <cstdio>
#include <cstring>

char a[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
char b[] = "A   3  HIL JM O   2TUVWXY51SE Z  8 0";
char out[4][50] = {
    " -- is not a palindrome.\n\n",
    " -- is a regular palindrome.\n\n",
    " -- is a mirrored string.\n\n",
    " -- is a mirrored palindrome.\n\n"};
int t[256], len;

int main(){
    for(int i = 0; a[i]; i++)
        t[a[i]] = i;
    char str[50];
    int mirror, palindrome;
    while(~scanf("%s", str)){
        len = strlen(str);
        mirror = 2;
        for(int i = 0; i <= len / 2; i++){
            if(str[i] != b[t[str[len-1-i]]]){
                mirror = 0;
                break;
            }
        }
        palindrome = 1;
        for(int i = 0; i < len / 2; i++){
            if(str[i] != str[len-1-i]){
                palindrome = 0;
                break;
            }
        }
        printf("%s%s", str, out[mirror + palindrome]);
    }
}
