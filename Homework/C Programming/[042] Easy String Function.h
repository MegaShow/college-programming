/*
 *	Name: [042] Easy String Function
 *	Author: Mega Show
 *	Date: 2016.12.45
 */

#ifndef MYSTRING_H_
#define MYSTRING_H_

int myStrlen(char a[]){
    int len = 0;
    while(a[len] != 0)
        len++;
    return len;
}

int myStrcmp(char a[], char b[]){
    for(int i = 0; a[i] != 0 && b[i] != 0 ; i++){
        if(a[i] != b[i])
            return a[i] - b[i];
    }
    return 0;
}

void myStrcpy(char des[], char src[]){
    int i;
    for(i = 0; src[i] != 0; i++)
        des[i] = src[i];
    des[i] = 0;
}

#endif
