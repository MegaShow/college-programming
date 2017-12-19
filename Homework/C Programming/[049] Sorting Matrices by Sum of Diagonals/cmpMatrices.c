/*
 *  File: cmpMatrices.c
 *	Name: [049] Sorting Matrices by Sum of Diagonals
 *	Author: Mega Show
 *	Date: 2016.12.3 11:52
 */

#include <stdio.h>
#include <stdlib.h> 
#include "cmpMatrices.h"

void inputMatrices(int arr[][MAX_SIZE], size_t size){
	for(int i = 0; i < size; i++)
		for(int j = 0; j < size; j++)
			scanf("%d", &arr[i][j]);
}

void printMatrices(int arr[][MAX_SIZE], size_t size){
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size - 1; j++)
			printf("%d ", arr[i][j]);
		printf("%d\n", arr[i][size-1]);
	}
	printf("\n");
}

int cmpMatrices(const void *firstMatrixPtr, const void *secondMatrixPtr, void *sizePtr){
	//int firstArr[MAX_SIZE][MAX_SIZE];
	int* firstArr = *((int(*)[MAX_SIZE])firstMatrixPtr);
	//int secondArr[MAX_SIZE][MAX_SIZE];
	int* secondArr = *((int(*)[MAX_SIZE])secondMatrixPtr);
	size_t size = *((size_t*)sizePtr);
	int first = 0, second = 0;
	for(int i = 0; i < size; i++)
		for(int j = 0; j < size; j++)
			if(i == j || i + j == size - 1){
				first += *(firstArr + MAX_SIZE * i + j);
				second += *(secondArr + MAX_SIZE * i + j);
			}
	return (first - second);
}