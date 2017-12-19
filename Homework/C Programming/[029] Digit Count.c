/*
 *	Name: [029]Digit Count
 *	Author: Mega Chan
 *	Date: 2016.11.1 13:42
 */
 
#include <stdio.h>

int main(){
    int num, var, temp, digit[10];
    scanf("%d",&num);
    for(int i = 0;i < num;i++){
        scanf("%d",&var);
        for(int j = 0;j < 10;j++)
            digit[j] = 0;
        for(int j = 0;j <= var;j++){
            temp = j;
            while(temp){
                digit[temp%10]++;
                temp /= 10;
            }
        }
        for(int j = 0;j < 9;j++)
            printf("%d ",digit[j]);
        printf("%d\n",digit[9]);
     }
}