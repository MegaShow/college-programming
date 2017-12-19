/*
 *	Name: [2016 C Midterm B] Modulus of Reverse
 *	Author: Mega Show
 *	Date: 2016.12.22
 */

#include <stdio.h>
#include <string.h>

int main(){
    int n, p, var, sum;
    char arr[1000];
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%d%s", &p, arr);
        var = 0;
        for(int i = strlen(arr) - 1; i >= 0; i--)
            var = (var * 10 + arr[i] - '0') % p;
        printf("%d\n", var);
    }
    return 0;
}
