/* 11598 XOR */

#include <cstdio>

int main(){
    int num, a, b, xa, xb, va, vb;
    scanf("%d", &num);
    for(int i = 0; i < num; i++){
        va = vb = 0;
        scanf("%d%d", &a, &b);
        a--;
        xa = (a + 1) % 4;
        for(int i = 1; i <= xa; i++)
            va ^= (a--);
        xb = (b + 1) % 4;
        for(int i = 1; i <= xb; i++)
            vb ^= (b--);
        printf("%d\n", va^vb);
    }
    return 0;
}
