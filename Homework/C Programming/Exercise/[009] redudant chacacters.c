/*
 *	Name: [027]redudant chacacters
 *	Author: Mega Chan
 *	Date: 2016/10/31 16:58
 */

#include <stdio.h>
#include <string.h>

int main(){
    char str[100],out[100];
    int top = 1, is_eq = 0;
    scanf("%s",str);
    int len = strlen(str);
    out[0] = str[0];
    for(int i = 1;i < len;i++){
        for(int j = 0;j < top;j++){
            if(str[i] == out[j]){
                is_eq = 1;
                break;
            }
            is_eq = 0;
        }
        if(is_eq == 0){
            out[top] = str[i];
            top++;
        }
    }
    printf("%s\n",out);
    return 0;
}