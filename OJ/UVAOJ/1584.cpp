// UVA1584 MegaShow 2017.2.3

#include <cstdio>
#include <cstring>

int main(){
    int n, index, len;
    char str[102];
    scanf("%d", &n);
    while(n--){
        index = 0;
        scanf("%s", str);
        len = strlen(str);
        for(int i = 1; i < len; i++){
            for(int j = 0; j < len; j++){
                if(str[(i+j)%len] < str[(index+j)%len]){
                    index = i;
                    break;
                }
                else if(str[(i+j)%len] > str[(index+j)%len])
                    break;
            }
        }
        for(int i = 0; i < len; i++)
            printf("%c", str[(index+i)%len]);
        printf("\n");
    }
}
