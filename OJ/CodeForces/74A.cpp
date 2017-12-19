// CodeForces 74A MegaShow 2017.2.9

#include <cstdio>
#include <cstring>

int main(){
    char name[25], out[25];
    int n, score, max = 0, hacker, fail, var;
    scanf("%d", &n);
    for(int j = 0; j < n; j++){
        scanf("%s%d%d", name, &hacker, &fail);
        score = hacker * 100 - fail * 50;
        for(int i = 0; i < 5; i++){
            scanf("%d", &var);
            score += var;
        }
        if(max < score || j == 0){
            max = score;
            strcpy(out, name);
        }
    }
    printf("%s\n", out);
}
