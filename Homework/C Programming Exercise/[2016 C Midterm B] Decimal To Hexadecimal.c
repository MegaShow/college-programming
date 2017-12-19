/*
 *	Name: [2016 C Midterm B] Decimal To Hexadecimal
 *	Author: Mega Show
 *	Date: 2016.12.28
 */

#include <stdio.h>

int main(){
    int var, p;
    scanf("%d", &var);
    if(var == 0)
        printf("0");
    while(var){
        p = var % 16;
        if(p <= 9)
            printf("%d", p);
        else
            printf("%c", p - 10 + 'A');
        var /= 16;
    }
    printf("\n");
    return 0;
}
