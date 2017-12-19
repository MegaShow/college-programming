/*
ID: megaxiu1
LANG: C++
TASK: gift1
*/

#include <cstdio>
#include <cstring>

char name[10][20];
int menoy[10];

int GetIndex(char param_name[20]){
    int index = 0;
    while(strcmp(name[index], param_name))
        index++;
    return index;
}

int main(){
    freopen("gift1.in", "r", stdin);
    freopen("gift1.out", "w", stdout);
    int np, var, n, index;
    char get_name[20];
    scanf("%d", &np);
    for(int i = 0; i < np; i++)
        scanf("%s", name[i]);
    for(int i = 0; i < np; i++){
        scanf("%s", get_name);
        scanf("%d%d", &var, &n);
        if(n == 0)
            continue;
        index = GetIndex(get_name);
        menoy[index] -= var / n * n;
        for(int k = 0; k < n; k++){
            scanf("%s", get_name);
            index = GetIndex(get_name);
            menoy[index] += var / n;
        }
    }
    for(int i = 0; i < np; i++)
        printf("%s %d\n", name[i], menoy[i]);
}
