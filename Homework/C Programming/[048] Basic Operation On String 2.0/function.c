/*
 *  File: function.c
 *	Name: [048] Basic Operation On String 2.0
 *	Author: Mega Show
 *	Date: 2016.11.28 20:17
 */
 
#include <string.h>
#include "function.h"

/**
 * split a string into some words with del as delimiter
 * @param ret is a container to store the words
 * @param str is the string to be split
 * @param del is the delimiter
 * @return the number of words
 */
int split(char ret[][100], const char str[], const char del){
	int index = -1;
	int len = strlen(str);
	for(int i = 0; i <= len; i++){
		index++;
		if(i == len)
			break;
		for(int k = 0; str[i] != del && str[i] != 0; k++)
			ret[index][k] = str[i++];
	}
	return index + 1;
}


/**
 * remove the leading characters which are equal to del
 * @param str is the string to be handled
 * @param del is the character should be removed
 */
void lstrip(char str[], const char del){
	int index = 0, i = 0, k;
	int len = strlen(str);
	while(str[index] == del)
		index++;
	k = index;
	while(k <= len)
		str[i++] = str[k++];
}


/**
 * remove the trailing characters which are equal to del
 * @param str is the string to be handled
 * @param del is the character should be removed
 */
void rstrip(char str[], const char del){
	int index = strlen(str) - 1;
	while(str[index] == del)
		index--;
	str[index+1] = 0;
}


/**
 * remove the leading and trailing characters 
 * which are equal to del
 * @param str is the string to be handled
 * @param del is the character should be removed
 */
void strip(char str[], const char del){
	lstrip(str, del);
	rstrip(str, del);
}