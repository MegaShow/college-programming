/*
 *	Name: snake2.h
 *	Author: Mega Show
 *	Date: 2016.12.19
 */

#ifndef SNAKE_2_H_
#define SNAKE_2_H_


/**********************************************************************************
 *  Definition of structs and some variables
 **********************************************************************************/
 typedef enum { ERROR, UP, DOWN, LEFT, RIGHT } InputKey;
 typedef enum { true = 1, false = 0, eof = -1 } bool;

#define SNAKE_HEAD 'H'
#define SNAKE_BODY 'X'
#define MAP_SPACE ' '
#define MAP_WALL '*'
#define FOOD '$'

#define MAX_WIDTH 25
#define MAX_HEIGHT 30

char map[MAX_WIDTH][MAX_HEIGHT];
const int width = 10;
const int height = 10;
int food_x;
int food_y;
bool is_init_seed_random = false;

struct list{
    struct node * head;
    int length;
};

struct node{
    struct node * next;
    int x;
    int y;
};

typedef struct list* List;
typedef struct node* Node;
typedef List Player;

#define NODE_SIZE sizeof(struct node)
#define LIST_SIZE sizeof(struct list)


/**********************************************************************************
 *  Function about Game
 **********************************************************************************/
void CreateNewGame(Player* l);
bool CreateRandomFood(Player l);
InputKey GetInput();
bool MovePlayer(Player l, InputKey input);
void DrawMap();
void UpdateMap(Player l);
void GameOver(Player* l, bool is_alive);


/**********************************************************************************
 *  Function about List
 **********************************************************************************/
void InitList(List* l);
void AddNodeAtHead(List l, int x, int y);
bool DeleteNodeAtLast(List l);
void DeleteList(List* l);

#endif /* SNAKE_2_H_ */
