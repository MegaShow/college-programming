/*
 *	Name: [054] Simple Game
 *	Author: Mega Show
 *	Date: 2016.12.6
 */
 
#include <stdio.h>
#include <stdlib.h>
#include "utility.h"

char c;  // store the opreating of move

int main(){
	size_t length;
	int is_alive = 1, is_stop = 0;
	scanf("%u", &length);
	getchar();
	readMap(length);
	while(~scanf("%c", &c)){
		move(length, &is_alive, &is_stop);
		if(is_alive)
			printMap(length);
		else{
			printf("Game Over!\n");
			return 0;
		}
		getchar();
	}
	return 0;
}

/* read the map from stdin. */
void readMap(const size_t map_size){
	for(size_t i = 0; i < map_size + 2; i++){
		for(size_t j = 0; j < map_size + 2; j++){
			scanf("%c", &map[i][j]);
			if(map[i][j] == 'A'){
				human_x = j;
				human_y = i;
			}
		}
		getchar();
	}
}

/* print the map while human is alive. */
void printMap(const size_t map_size){
	for(size_t i = 0; i < map_size + 2; i++){
		for(size_t j = 0; j < map_size + 2; j++){
			printf("%c", map[i][j]);
		}
		printf("\n");
	}
}

/* move the human in map */
/* when is_stop = -1, it means the last step is stop. */
void move(size_t map_size, int *is_alive, int *is_stop){
	if(*is_stop == 1){
		*is_stop = -1;
		return;
	}
	int x, y;
	switch(c){
		case 'w': x = human_x; y = (human_y == 1 ? map_size : human_y - 1); break;
		case 's': x = human_x; y = (human_y == map_size ? 1 : human_y + 1); break;
		case 'a': y = human_y; x = (human_x == 1 ? map_size : human_x - 1); break;
		case 'd': y = human_y; x = (human_x == map_size ? 1 : human_x + 1); break;
	}
	if(map[y][x] != '#'){
		if(map[y][x] == '@')
			*is_stop = 1;
		else if(map[y][x] == '$')
			*is_alive = 0;
		if(*is_stop == -1){
			*is_stop = 0;
			map[human_y][human_x] = '@';
		}
		else
			map[human_y][human_x] = ' ';
		map[y][x] = 'A';
		human_x = x;
		human_y = y;
	}
}