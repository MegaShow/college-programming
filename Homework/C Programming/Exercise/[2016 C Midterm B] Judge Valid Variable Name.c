/*
 *	Name: [2016 C Midterm B] Judge Valid Variable Name
 *	Author: Mega Show
 *	Date: 2016.12.26
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int IsValid(char arr[]){
    if(arr[0] == '_' || isupper(arr[0]) || islower(arr[0])){
        for(int i = 1; arr[i] != 0; i++){
            if(arr[i] == '_' || isupper(arr[i]) || islower(arr[i]) || isdigit(arr[i]))
                continue;
            return 0;
        }
        return 1;
    }
    return 0;
}

int main(){
    int n;
    char arr[64];
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%s", arr);
        if(IsValid(arr))
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}
