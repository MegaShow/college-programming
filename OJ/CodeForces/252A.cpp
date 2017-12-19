// CodeForces 252A MegaShow 2017.2.9

#include <cstdio>

int main(){
    int n, max = 0, var;
    scanf("%d", &n);
    int xor_n[n+1] = {0};
    for(int i = 1; i <= n; i++){
        scanf("%d", &var);
        xor_n[i] = xor_n[i-1] ^ var;
        for(int j = 0; j < i; j++){
            if(max < (xor_n[i] ^ xor_n[j])){
                max = xor_n[i] ^ xor_n[j];
            }
        }
    }
    printf("%d", max);
}
