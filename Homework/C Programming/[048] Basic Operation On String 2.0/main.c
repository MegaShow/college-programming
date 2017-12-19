/*
 *  File: main.c
 *	Name: [048] Basic Operation On String 2.0
 *	Author: Mega Show
 *	Date: 2016.11.28 20:16
 */
 
#include <stdio.h>
#include <string.h>
#include "function.h"

/*int getstr(char str[], char* pdel){
	fgets(str, 100, stdin);
	int len = strlen(str);
	str[len-1] = 0;
	scanf("%c", pdel);
	getchar();
}*/
int getstr(char str[], char* pdel){
	scanf("%[^\n]", str);
	getchar();
	scanf("%c", pdel);
	getchar();
}

int main(){
	char ret[100][100] = {0};
	char str[100];
	char del;

	getstr(str, &del);
	int word = split(ret, str, del);
	for(int i = 0; i < word; i++)
		printf("%s\n", ret[i]);

	getstr(str, &del);
	lstrip(str, del);
	printf("%s\n", str);
	rstrip(str, del);
	printf("%s\n", str);

	getstr(str, &del);
	strip(str, del);
	printf("%s\n", str);

	return 0;
}