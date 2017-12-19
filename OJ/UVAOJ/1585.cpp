// UVA1585 MegaShow 2017.2.3

#include <cstdio>

int main(){
    int n, c, score, var;
    scanf("%d", &n);
    getchar();
    while(n--){
        score = var = 0;
        while((c = getchar()) != '\n'){
            if(c == 'O')
                score += (++var);
            else
                var = 0;
        }
        printf("%d\n", score);
    }
}
