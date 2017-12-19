/*
 *	Name: [065] [I 1001] 兔子问题
 *	Author: Mega Show
 *	Date: 2016.12.25
 */

#include <stdio.h>

int arr[48] = {0, 2, 2};

int main(){
    for(int i = 3; i < 48; i++)
        arr[i] = arr[i-1] + arr[i-2];
    int var;
    while(~scanf("%d", &var)){
        if(var == -1)
            break;
        printf("%d\n", arr[var]);
    }
    return 0;
}
