/*
 *	Name: [041] Sway Array and Matrix
 *	Author: Mega Show
 *	Date: 2016.12.24
 */

#ifndef MYSWAP_H_
#define MYSWAP_H_

void swapArray(int len, int a[], int b[]){
    int temp;
    for(int i = 0; i < len; i++){
        temp = a[i];
        a[i] = b[i];
        b[i] = temp;
    }
}

void swapMatrix(int len, int a[][len], int b[][len]){
    int temp;
    for(int i = 0; i < len; i++){
        for(int k = 0; k < len; k++){
            temp = a[i][k];
            a[i][k] = b[i][k];
            b[i][k] = temp;
        }
    }
}

#endif
