/* Written by Matrix */

#include "myswap.h"
#include <stdio.h>

#define MAX_LEN 5

void inputArray(int len, int arr[len]) {
  for (int i = 0; i < len; ++i)
    scanf("%d", &arr[i]);
}

void printArray(int len, int arr[len]) {
  for (int i = 0; i < len; ++i) {
    if (i == 0) printf("%d", arr[i]);
    else printf(" %d", arr[i]);
  }
  printf("\n");
}

void inputMatrix(int len, int mat[len][len]) {
  for (int i = 0; i < len; ++i) {
    for (int j = 0; j < len; ++j) {
      scanf("%d", &mat[i][j]);
    }
  }
}

void printMatrix(int len, int mat[len][len]) {
  for (int i = 0; i < len; ++i) {
    for (int j = 0; j < len; ++j) {
      if (j == 0) printf("%d", mat[i][j]);
      else printf(" %d", mat[i][j]);
    }
    printf("\n");
  }
}

int main() {
  int arr1[MAX_LEN] = {}, arr2[MAX_LEN] = {};
  int mat1[MAX_LEN][MAX_LEN] = {}, mat2[MAX_LEN][MAX_LEN] = {};

  // Input Array
  printf("Input array1\n");
  inputArray(MAX_LEN, arr1);
  printf("Input array2\n");
  inputArray(MAX_LEN, arr2);

  // Input Matrix
  printf("Input matrix1\n");
  inputMatrix(MAX_LEN, mat1);
  printf("Input matrix2\n");
  inputMatrix(MAX_LEN, mat2);

  // Swap them
  swapArray(MAX_LEN, arr1, arr2);
  swapMatrix(MAX_LEN, mat1, mat2);
  printf("Swapped.\n");

  printf("Array1:\n");
  printArray(MAX_LEN, arr1);
  printf("\n");
  printf("Array2:\n");
  printArray(MAX_LEN, arr2);
  printf("\n");

  printf("Matrix1:\n");
  printMatrix(MAX_LEN, mat1);
  printf("\n");
  printf("Matrix2:\n");
  printMatrix(MAX_LEN, mat2);

  return 0;
}
