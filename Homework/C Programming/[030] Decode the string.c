/*
 *	Name: [030]Decode the string
 *	Author: Mega Chan
 *	Date: 2016.11.5 21:54
 */

#include <stdio.h>
#include <string.h>

int main(){
	char str[100];
	scanf("%s", str);
	int var, len = strlen(str);
	for(int i = 0, j = 1; i < len; i = j){
		var = 0;
		for(j=i+1; str[j]>='0' && str[j]<='9'; j++)
			var = var * 10 + str[j] - '0';
		if(var > 7)
			var = var % 7 + 1;
		else if(var == 0)
			var = 1;
		for(int k = 0; k < var; k++)
			printf("%c", str[i]);
	}
	printf("\n");
	return 0;
}