/*
 *	Name: [2016 C Midterm B] Print Multiplication Table
 *	Author: Mega Show
 *	Date: 2016.12.24
 */

#include <stdio.h>

int main(){
    int a, b;
    scanf("%d%d", &a, &b);
    for(int i = a; i <= b; i++){
        printf("1*%d=%d", i, i);
        for(int k = 2; k <= i; k++)
            printf("  %d*%d=%d", k, i, k * i);
        printf("\n");
    }
    return 0;
}
