// UVA455 MegaShow 2017.2.3

#include <cstdio>
#include <cstring>

bool check(char str[], int out){
    for(int i = 0; str[i]; i++){
        if(str[i] != str[i%out])
            return false;
    }
    return true;
}

int main(){
    int n, out, len, flag = 0;
    char str[100];
    scanf("%d", &n);
    while(n--){
        scanf("%s", str);
        len = strlen(str);
        out = 1;
        while(check(str, out) == false){
            out++;
            while(len % out)
                out++;
        }
        if(flag++)
            printf("\n");
        printf("%d\n", out);
    }
}
