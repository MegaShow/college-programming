/* 4312 A+B */

#include <cstdio>

int re(int var){
    int sum = 0;
    while(var){
        sum = sum * 10 + var % 10;
        var /= 10;
    }
    return sum;
}

int main(){
    int num, a, b;
    scanf("%d", &num);
    for(int i = 0; i < num; i++){
        scanf("%d%d", &a, &b);
        printf("%d\n", re(a)+re(b));
    }
    return 0;
}
