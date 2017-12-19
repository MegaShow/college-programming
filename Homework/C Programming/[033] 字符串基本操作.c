/*
 *	Name: [033]字符串基本操作
 *	Author: Mega Chan
 *	Date: 2016.11.9 10:38
 */
 
//char * strncat(char *dest, const char *src, size_t n);

#include <stdio.h>
#include <string.h>

void cmp_print(const char * str1, const char * str2){
	if(strcmp(str1,str2) > 0)
		printf("%s > %s\n", str1, str2);
	else if(strcmp(str1,str2) == 0)
		printf("%s = %s\n", str1, str2);
	else
		printf("%s < %s\n", str1, str2);
}

int main(){
	char str1[50], str2[50];
	int n, x, y;
	scanf("%s%s%d%d%d", str1, str2, &n, &x, &y);
	cmp_print(str1, str2);
	strncat(str1, str2, n);
	for(int i = x; i <= y; i++)
		if(str1[i] >= 'a' && str1[i] <= 'z')
			str1[i] += ('A'-'a');
	printf("the length of \"%s\" is %d\n", str1, strlen(str1));
	strcpy(str2, str1);
	for(int i = 0; str2[i] != 0; i++)
		if(str2[i] >= 'A' && str2[i] <= 'Z')
			str2[i] += ('a'-'A');
	cmp_print(str1,str2);
	if(strlen(str1)/2 > 10)
		printf("%s\n", str1);
	else
		printf("%s\n", str2);
	return 0;
}