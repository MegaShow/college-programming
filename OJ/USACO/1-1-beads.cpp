/*
ID: megaxiu1
LANG: C++
TASK: beads
*/

#include <cstdio>
#include <cstring>

int n;

int judge(char str[], int i, char lhs, char rhs, int &max){
    int lhsv = 1, rhsv = 1;
    int j = i - 1, k = i + 1;
    for(j = i - 2; j >= 0 && k <= n + j; j--){
        if(str[j] == lhs || str[j] == 'w')
            lhsv++;
        else
            break;
    }
    for(k = i + 1; k < 2 * n && k <= n + j; k++){
        if(str[k] == rhs || str[k] == 'w')
            rhsv++;
        else
            break;
    }
    if(max < lhsv + rhsv)
        max = lhsv + rhsv;
}

int main(){
    freopen("beads.in", "r", stdin);
    freopen("beads.out", "w", stdout);

    int max = 0;
    scanf("%d", &n);
    char str[2*n+1], lhs, rhs;
    scanf("%s", str);
    memcpy(str + n, str, n);
    str[2*n] = 0;
    for(int i = 1; i < 2 * n; i++){
        lhs = str[i-1];
        rhs = str[i];
        if(lhs == 'w'){
            judge(str, i, 'r', rhs, max);
            judge(str, i, 'b', rhs, max);
        }
        else if(rhs == 'w'){
            judge(str, i, lhs, 'r', max);
            judge(str, i, lhs, 'b', max);
        }
        else
            judge(str, i, lhs, rhs, max);
    }
    printf("%d\n", max);
}
