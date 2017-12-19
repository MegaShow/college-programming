/*
 *	Name: Count and Histogram
 *	Author: Mega Chan
 *	Date: 2016/10/29 10:41
 */

#include <stdio.h>
#include <string.h>

int main () {
	char str[400];
	int len, max = 0, num = 0, str_num = 0, alphabet[26] = {0};
	while(EOF != scanf("%s", str)){
		str_num++;
		len = strlen(str);
		for(int i = 0;i < len;i++)
			alphabet[str[i]-'a']++; 
	}
	for(int i = 0;i < 26;i++){
		if(0 != alphabet[i])
			num++;
		else
			alphabet[i] = -1;
		if(max < alphabet[i])
			max = alphabet[i];
	}
	if(max < str_num)
		max = str_num;
	for(int i = max;i > 0;i--){
		printf("%d\t", i);
		for(int j = 0;j < 26;j++){
			if(alphabet[j] == i){
				printf("*");
				alphabet[j]--;
			}	
			else if(alphabet[j] != -1)
				printf(" ");
		}
		if(i == str_num){
			printf("*\n");
			str_num--;
		}
		else
			printf(" \n");
	} 
	printf(" \t");
	for(int i = 0;i < 26;i++)
		if(alphabet[i] != -1)
			printf("%c", i+'a');
	printf("W\n");
	return 0;
} 
