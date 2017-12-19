/*
 *	Name: [043] 异构体
 *	Author: Mega Show
 *	Date: 2016.11.21 17:21
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(void* a, void* b){
	return (*(char*)a) - (*(char*)b);
}

int main(){
	char str1[51], str2[51];
	scanf("%s%s", str1, str2);
	qsort(str1, strlen(str1), sizeof(char), compare);
	qsort(str2, strlen(str2), sizeof(char), compare);
	if(strcmp(str1, str2) == 0)
		printf("YES\n");
	else
		printf("NO\n");
	return 0;
}