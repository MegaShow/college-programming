/*
 *  File: cmpMatrices.h
 *	Name: [049] Sorting Matrices by Sum of Diagonals
 *	Author: Mega Show
 *	Date: 2016.12.3 11:52
 */
 
#ifndef CMPMATRICES_H
#define CMPMATRICES_H

#define MAX_TOTAL 10
#define MAX_SIZE 4


void inputMatrices(int arr[][MAX_SIZE], size_t size);

void printMatrices(int arr[][MAX_SIZE], size_t size);

int cmpMatrices(const void *firstMatrixPtr, const void *secondMatrixPtr, void *sizePtr);

#endif