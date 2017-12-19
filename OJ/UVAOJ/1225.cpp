// UVA1225 MegaShow 2017.2.3

#include <cstdio>

int main(){
    int n, var, out[10];
    scanf("%d", &n);
    while(n--){
        for(int i = 0; i < 10; i++)
            out[i] = 0;
        scanf("%d", &var);
        for(int i = 1; i <= var; i++){
            int j = i;
            while(j){
                out[j%10]++;
                j /= 10;
            }
        }
        for(int i = 0; i <= 8; i++)
            printf("%d ", out[i]);
        printf("%d\n", out[9]);
    }
}
