/*
 *	Name: [2016 C Midterm B] Derivative of Polynomial
 *	Author: Mega Show
 *	Date: 2016.12.26
 */

#include <stdio.h>
#include <math.h>

int main(){
    int n, x, a, b, f = 0;
    scanf("%d%d", &n, &x);
    for(int i = 0; i < n; i++){
        scanf("%d%d", &a, &b);
        f = f + a * b * pow(x, b-1);
    }
    printf("%d\n", f);
    return 0;
}
