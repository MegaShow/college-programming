// UVA10082 MegaShow 2017.1.25

#include <cstdio>

char str[] = "`1234567890-=QWERTYUIOP[]\\ASDFGHJKL;\'ZXCVBNM,./";
int arr[256];

int main(){
    for(int i = 0; str[i]; i++)
        arr[str[i]] = i - 1;
    char c;
    while(~scanf("%c", &c)){
        if(arr[c] != 0)
            printf("%c", str[arr[c]]);
        else
            printf("%c", c);
    }
}


/*#include <cstdio>

char str[] = "`1234567890-=QWERTYUIOP[]\\ASDFGHJKL;\'ZXCVBNM,./";

int main(){
    char c;
    int i;
    while(~(c = getchar())){
        i = 0;
        while(str[i] && c != str[i])
            i++;
        if(str[i])
            printf("%c", str[i-1]);
        else
            printf("%c", c);
    }
}**/
