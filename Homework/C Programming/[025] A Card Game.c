/*
 *	Name: A Card Game
 *	Author: Mega Chan
 *	Date: 2016/10/29 11:56
 */

#include <stdio.h>

int main(){
	int n, var, num[5] = {0};
	scanf("%d",&n);
	for(int i = 0;i < n;i++){
		scanf("%d",&var);
		switch(var){
			case 0: num[0]++; break;
			case 3: num[1]++; break;
			case 5: num[2]++; break;
			case 7: num[3]++; break;
			case 9: num[4]++; break;
		}
	}
	if(num[0]==0 || (num[1]*3+num[2]*5+num[3]*7+num[4]*9)%3!=0 
				 || (num[1]==0&&num[2]==0&&num[3]==0&&num[4]==0))
		printf("no such number");
	else{
		while(num[4]>0){printf("9");num[4]--;}
		while(num[3]>0){printf("7");num[3]--;}
		while(num[2]>0){printf("5");num[2]--;}
		while(num[1]>0){printf("3");num[1]--;}
		while(num[0]>0){printf("0");num[0]--;}	
	}
	printf("\n");
	return 0;
}