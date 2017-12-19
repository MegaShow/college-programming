/*
 *	Name: [060] 汉诺塔
 *	Author: Mega Show
 *	Date: 2016.12.17
 */

#include <stdio.h>

void DFS(int n, int prevPeg, int nextPeg, int targetPeg){
    if(n == 1){
        printf("move disk 1 from peg %d to peg %d\n", prevPeg, targetPeg);
        return;
    }
    DFS(n - 1, prevPeg, targetPeg, nextPeg);
    printf("move disk %d from peg %d to peg %d\n", n, prevPeg, targetPeg);
    DFS(n - 1, nextPeg, prevPeg, targetPeg);
}

int main(){
    int num, n;
    scanf("%d", &num);
    for(int i = 0; i < num; i++){
        scanf("%d", &n);
        DFS(n, 1, 2, 3);
    }
    return 0;
}
