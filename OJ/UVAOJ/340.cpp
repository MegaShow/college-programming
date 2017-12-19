// UVA340 MegaShow 2017.2.3

#include <cstdio>
#include <cstring>

int r[1003];
int in[1003];
int rn[10];
int inn[10];

int main(){
    int n, lhs, rhs, game = 1;
    scanf("%d", &n);
    while(n){
        memset(rn, 0, sizeof(rn));
        memset(inn, 0, sizeof(inn));
        for(int i = 0; i < n; i++){
            scanf("%d", &r[i]);
            rn[r[i]]++;
        }
        for(int i = 0; i < n; i++){
            scanf("%d", &in[i]);
            inn[in[i]]++;
        }
        printf("Game %d:\n", game);
        game++;
        while(in[0]){
            lhs = rhs = 0;
            for(int i = 0; i < n; i++){
                if(r[i] == in[i])
                    lhs++;
            }
            for(int i = 1; i < 10; i++){
                rhs += (rn[i] < inn[i] ? rn[i] : inn[i]);
            }
            printf("    (%d,%d)\n", lhs, rhs - lhs);
            memset(inn, 0, sizeof(inn));
            for(int i = 0; i < n; i++){
                scanf("%d", &in[i]);
                inn[in[i]]++;
            }
        }
        scanf("%d", &n);
    }
}
