/*
 *	Name: [026]回文数
 *	Author: Mega Chan
 *	Date: 2016/10/31 13:59
 */

 #include <stdio.h>

 int main(){
     int num, var, sum, _var;
     scanf("%d",&num);
     for(int i = 0;i < num;i++){
         scanf("%d",&var);
         _var = var;
         sum = 0;
         while(var){
             sum = sum * 10 + var % 10;
             var /= 10;
         }
         if(sum == _var)
            printf("Yes\n");
        else
            printf("No\n");
     }
     return 0;
 }