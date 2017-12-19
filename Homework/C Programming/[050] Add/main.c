/* Written by Matrix */

#include <stdio.h>
#include "Oper.h"
int main() {
 	char lhs[8] = {}, rhs[8] = {}, sum[10] = {};
	scanf("%s %s", lhs, rhs);
	add(lhs, rhs, sum);
	printf("%s\n", sum);
	return 0;
}