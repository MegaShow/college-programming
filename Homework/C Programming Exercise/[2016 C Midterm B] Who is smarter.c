/*
 *	Name: [2016 C Midterm B] Who is smarter?
 *	Author: Mega Show
 *	Date: 2016.12.20
 */

#include <stdio.h>

int main(){
    int n, m, x, y = 1;
    scanf("%d%d", &n, &m);
    x = n * 365 % 400009;
    for(int i = 0; i < m; i++){
        for(int k = 0; k < 365; k++){
            y = (y << 1) % 400009;
        }
    }
    int sum = (y - x) % 400009;
    if(sum < 0)
        sum += 400009;
    printf("%d\n", sum);
    return 0;
}
