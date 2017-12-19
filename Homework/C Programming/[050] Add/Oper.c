/*
 *  File: Oper.c
 *	Name: [050] Add
 *	Author: Mega Show
 *	Date: 2016.12.1 23:47
 */
#define METHOD 1

#if METHOD == 1
#include <stdio.h>
#include <stdlib.h>
#include "Oper.h"

void add(char lhs[], char rhs[], char sum[]){
	int lnum = atoi(lhs);
	int rnum = atoi(rhs);
	sprintf(sum, "%d", lnum + rnum);
}

#elif METHOD == 2
#include <string.h>
#include "Oper.h"

void add(char lhs[], char rhs[], char sum[]){
	int llen = strlen(lhs), rlen = strlen(rhs);
	int slen = (llen > rlen ? llen : rlen) + 1;
	char temp = 0;
	sum[0] = sum[slen] = 0;
	int i, j, k;
	for(i=llen-1, j=rlen-1, k=slen-1; i>=0 && j>=0; k--){
		sum[k] = (lhs[i] - '0' + rhs[j] - '0' + temp) % 10 + '0';
		if((lhs[i--] - '0' + rhs[j--] - '0' + temp) / 10)
			temp = 1;
		else
			temp = 0;
	}
	while(i >= 0){
		sum[k--] = (lhs[i] - '0' + temp) % 10 + '0';
		if((lhs[i--] - '0' + temp) / 10)
			temp = 1;
		else
			temp = 0;
	}
	while(j >= 0){
		sum[k--] = (rhs[j] - '0' + temp) % 10 + '0';
		if((rhs[j--] - '0' + temp) / 10)
			temp = 1;
		else
			temp = 0;
	}
	if(temp)
		sum[0] = '1';
	else{
		for(int i = 0; i < slen; i++)
			sum[i] = sum[i+1];
	}
}
#endif