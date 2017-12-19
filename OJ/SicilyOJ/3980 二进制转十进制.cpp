/* 3980 二进制转十进制 */

#include <cstdio>

int main(){
    int num, var;
    char c;
    scanf("%d", &num);
    getchar();
    for(int i = 0; i < num; i++){
        var = 0;
        while((c = getchar()) != '\n'){
            var = var << 1;
            var += (int)(c - '0');
        }
        printf("%d\n", var);
    }
}
