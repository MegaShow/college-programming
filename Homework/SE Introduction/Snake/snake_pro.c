/*
 *	Name: snake_pro.c
 *	Author: Mega Show
 *	Date: 2016.12.25
 */

#include <stdio.h>
#include <time.h>

extern int width;
extern int height;
extern long snake_speed_sec;

int SetInfo(){
    char c;
    printf("Do you want to set for the game?(Default:N)(Y/N):");
    scanf("%c", &c);
    printf("\n");
    if(c == '\n' || c == 'N' || c == 'n')
        return 0;
    else if(c == 'Y' || c == 'y')
        return 1;
    else
        return -1;
}

int SetMapSize(){
    int size;
    printf("Set the width and height of the map.[Default:10](6~24):");
    scanf("%d", &size);
    printf("\n");
    return size;
}

int SetSpeed(){
    int level;
    printf("Set the level of snake's speed.[Default:2](1~3):");
    scanf("%d", &level);
    printf("\n");
    return level;
}

void GameSettings(){
    int var = SetInfo();
    while(var == -1)
        var = SetInfo();
    if(var){
        width = height = SetMapSize();
        while(width <= 5 || width >= 25)
            width = height = SetMapSize();
        var = SetSpeed();
        while(var <= 0 || var >= 4)
            var = SetSpeed();
        switch(var){
            case 1: snake_speed_sec = CLOCKS_PER_SEC / 2; break;
            case 2: snake_speed_sec = CLOCKS_PER_SEC / 3; break;
            case 3: snake_speed_sec = CLOCKS_PER_SEC / 6; break;
        }
    }
}
