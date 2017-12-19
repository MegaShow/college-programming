/* Made by Matrix */

#ifndef FUNCTION_H
#define FUNCTION_H

/**
 * split a string into some words with del as delimiter
 * @param ret is a container to store the words
 * @param str is the string to be split
 * @param del is the delimiter
 * @return the number of words
 */
int split(char ret[][100], const char str[], const char del);

/**
 * remove the leading characters which are equal to del
 * @param str is the string to be handled
 * @param del is the character should be removed
 */
void lstrip(char str[], const char del);

/**
 * remove the trailing characters which are equal to del
 * @param str is the string to be handled
 * @param del is the character should be removed
 */
void rstrip(char str[], const char del);

/**
 * remove the leading and trailing characters 
 * which are equal to del
 * @param str is the string to be handled
 * @param del is the character should be removed
 */
void strip(char str[], const char del);

#endif
