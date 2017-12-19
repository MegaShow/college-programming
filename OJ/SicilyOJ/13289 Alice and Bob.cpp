/* 13289 Alice and Bob */

#include <cstdio>

void BashGame(int n, int a, int b){
    if(n % (a + b) <= a && n % (a + b) > 0)
        printf("Bob\n");
    else
        printf("Alice\n");
}

int main(){
    int num, n, a, b;
    scanf("%d", &num);
    for(int i = 0; i < num; i++){
        scanf("%d%d%d", &n, &a, &b);
        BashGame(n, a, b);
    }
    return 0;
}
