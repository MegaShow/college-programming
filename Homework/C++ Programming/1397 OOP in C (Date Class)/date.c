// MegaShow
// [05] OOP in C (Date Class)
#include <stdio.h>
#include <stdlib.h>
#include "date.h"

Date* CreateDate(int year, int month, int day){
    Date* tmp = (Date*)malloc(sizeof(Date));
    tmp->year = year;
    tmp->month = month;
    tmp->day = day;
    return tmp;
}

void DestroyDate(Date** p){
    free(*p);
    *p = NULL;
}

Date* CopyDate(const Date* date){
    return CreateDate(date->year, date->month, date->day);
}

int GetYear(const Date* date){
    return date->year;
}

int GetMonth(const Date* date){
    return date->month;
}

int GetDay(const Date* date){
    return date->day;
}

void SetYear(Date* date, int year){
    date->year = year;
}

void SetMonth(Date* date, int month){
    date->month = month;
}

void SetDay(Date* date, int day){
    date->day = day;
}

void SetDate(Date* date, int year, int month, int day){
    SetYear(date, year);
    SetMonth(date, month);
    SetDay(date, day);
}

char* GetDateString(const Date* date){
    char* str = (char*)malloc(20);
    sprintf(str, "%04d-%02d-%02d", date->year, date->month, date->day);
    return str;
}

void DestroyDateString(char** p){
    free(*p);
    *p = NULL;
}

void IncreaseDate(Date* date){
    int arr[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if(date->month == 2 &&
        ( (date->year % 4 == 0 && date->year % 100 != 0) || date->year % 400 == 0 )){
        arr[0] = 29;
    }
    else
        arr[0] = arr[date->month];
    if(date->day == arr[0]){
        if(date->month == 12){
            date->year++;
            date->month = 1;
        }
        else
            date->month++;
        date->day = 1;
    }
    else
        date->day++;
}

void DecreaseDate(Date* date){
    int arr[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if(date->month == 3 &&
        ( (date->year % 4 == 0 && date->year % 100 != 0) || date->year % 400 == 0 )){
        arr[0] = 29;
    }
    else if(date->month == 1)
        arr[0] = arr[12];
    else
        arr[0] = arr[date->month-1];
    if(date->day == 1){
        if(date->month == 1){
            date->year--;
            date->month = 12;
        }
        else
            date->month--;
        date->day = arr[0];
    }
    else
        date->day--;
}
