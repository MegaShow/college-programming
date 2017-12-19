/*
 *	Name: [039] Fraction Multipe
 *	Author: Mega Chan
 *	Date: 2016.11.14 16:59
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

int main(){
	int num, a, b, c, d, var;
	scanf("%d", &num);
	for(int i = 0; i < num; i++){
		scanf("%d%d%d%d", &a, &b, &c, &d);
		if(b == 0 || d == 0)
			printf("Not A Number\n");
		else if(a == 0 || c == 0)
			printf("0\n");
		else{
			var = gcd(a*c, b*d);
			if(var == b*d)
				printf("%d\n", a*c/var);
			else 
				printf("%d/%d\n", a*c/var, b*d/var);
		}
	}
	return 0;
}