/*
 *	Name: [034] Replace the Character
 *	Author: Mega Show
 *	Date: 2016.12.24
 */

#include <stdio.h>

char arr['z'+1];
char str;

int main(){
    int n;
    char index;
    scanf("%d", &n);
    while(str != '\n')
        str = getchar();
    for(int i = 'a', j = 'A'; i <= 'z'; i++, j++){
        arr[i] = i;
        arr[j] = j;
    }
    for(int i = 0; i < n; i++){
        str = getchar();
        getchar();
        index = getchar();
        getchar();
        arr[index] = str;
    }
    while((index = getchar()) != '\n')
        printf("%c", arr[index]);
    printf("\n");
    return 0;
}


for(int i = 0; i < n; i++){
    scanf("%d", &var);
    printf("%d\n", arr[var]);
}
