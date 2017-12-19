/*
 *	Name: [037] The GCD and LCM
 *	Author: Mega Chan
 *	Date: 2016.11.18 19:49
 */
 
#include <stdio.h>

int gcd(int a, int b){
	int c = a % b;
	while(c){
		a = b;
		b = c;
		c = a % b;
	}
	return b;
}

int lcm(int a, int b){
	return a * b / gcd(a,b);
}

int main(){
	int a,b;
	scanf("%d%d", &a, &b);
	if(a <= 0 || b <= 0)
		printf("invalid\n");
	else
		printf("%d %d\n", gcd(a,b), lcm(a,b));
	return 0;
}