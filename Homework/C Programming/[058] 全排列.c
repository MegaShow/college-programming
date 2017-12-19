/*
 *	Name: [058] 全排列
 *	Author: Mega Show
 *	Date: 2016.12.16
 */

#include <stdio.h>

int n;
int arr[9];
int flag[9];

void DFS(int var){
    if(var == n + 1){
        for(int i = 1; i < var - 1; i++)
            printf("%d ", arr[i]);
        printf("%d\n", arr[var-1]);
        return;
    }
    for(int i = 1; i <= n; i++){
        if(flag[i] == 0){
            arr[var] = i;
            flag[i] = 1;
            DFS(var + 1);
            flag[i] = 0;
        }
    }
}

int main(){
    scanf("%d", &n);
    DFS(1);
}
