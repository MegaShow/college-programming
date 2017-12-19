/*
 *	Name: Pascal's Triangle
 *	Author: Mega Chan
 *	Date: 2016/10/29 11:22
 */

#include <stdio.h>

int com(int r,int c){

}

int main(){
	int var;
	scanf("%d",&var);
	int num[32];
	for(int i = 0;i < 32;i++)
		num[i] = 1;
	for(int i = 0;i < var;i++){
		for(int j = i;j < var - 1;j++)
			printf(" ");
		for(int j = 0;j <= i;j++){
			printf("%d",num[j]);
			if(j != i)
				printf(" ");
		}
		printf("\n");
		if(i >= 1)
			for(int j = i;j > 0;j--)
				num[j] += num[j-1];
	}
	return 0;
}
