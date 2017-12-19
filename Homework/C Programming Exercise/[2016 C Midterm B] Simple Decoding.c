/*
 *	Name: [2016 C Midterm B] Simple Decoding
 *	Author: Mega Show
 *	Date: 2016.12.25
 */

#include <stdio.h>

int main(){
    int var;
    char c;
    while((c = getchar()) != '\n'){
        var = 0;
        var = getchar() - '0';
        var = var * 10 + getchar() - '0';
        if(c == '0'){
            if(var == 0)
                printf(" ");
            else
                printf("%c", 'a' - 1 + var);
        }
        else{
            printf("%c", 'A' - 1 + var);
        }
    }
    printf("\n");
    return 0;
}
