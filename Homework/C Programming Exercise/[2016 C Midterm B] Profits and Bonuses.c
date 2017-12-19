/*
 *	Name: [2016 C Midterm B] Profits and Bonuses
 *	Author: Mega Show
 *	Date: 2016.12.19
 */

#include <stdio.h>

int main(){
    int n;
    double var;
    double sum;
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%lf", &var);
        if(var <= 100000)
            sum = var / 10;
        else if(var <= 200000)
            sum = 10000 + (var - 100000) * 7.5 / 100;
        else if(var <= 400000)
            sum = 10000 + 7500 + (var - 200000) * 5 / 100;
        else if(var <= 600000)
            sum = 10000 + 7500 + 10000 + (var - 400000) * 3 / 100;
        else if(var <= 1000000)
            sum = 10000 + 7500 + 10000 + 6000 + (var - 600000) * 1.5 / 100;
        else
            sum = 10000 + 7500 + 10000 + 6000 + 6000 + (var - 1000000) / 100;
        printf("%.0lf\n", sum);
    }
}

/*int main(){
    int n, var, sum;
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%d", &var);
        sum = 0;
        if(var > 1e6){
            sum += (var - 1e6) * 1 / 100;
            var = 1e6;
        }
        if(var > 6e5){
            sum += (var - 6e5) * 1.5 / 100;
            var = 6e5;
        }
        if(var > 4e5){
            sum += (var - 4e5) * 3 / 100;
            var = 4e5;
        }
        if(var > 2e5){
            sum += (var - 2e5) * 5 / 100;
            var = 2e5;
        }
        if(var > 1e5){
            sum += (var - 1e5) * 7.5 / 100;
            var = 1e5;
        }
        if(var > 0){
            sum += var * 10 / 100;
            var = 0;
        }
        printf("%d\n", sum);
    }
    return 0;
}*/
