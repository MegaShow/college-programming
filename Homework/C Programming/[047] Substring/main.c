/* Written by Matrix */

#include <stdio.h>
#include "substring.h"

int main () {
	char a[100], b[100];
	scanf("%s%s", a, b);
	int count = getNumOfSubstring(a, b);
	printf("%d\n", count);
	return 0;
}
