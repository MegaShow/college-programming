/*
 *	Name: snake.h
 *	Author: Mega Show
 *	Date: 2016.12.25
 */

#ifndef SNAKE_H_
#define SNAKE_H_


#define SNAKE_PRO  /* using snake_pro.c */
/**********************************************************************************
 *  Extern definition in snake_pro.c
 **********************************************************************************/
int width = 10;
int height = 10;
long snake_speed_sec = CLOCKS_PER_SEC / 3;

#ifdef SNAKE_PRO
extern void GameSettings();
#else
void GameSettings(){ return; }
#endif

/**********************************************************************************
 *  Definition of structs and some variables
 **********************************************************************************/
typedef enum { None, ERROR, UP, DOWN, LEFT, RIGHT } InputKey;
typedef enum { true = 1, false = 0, eof = -1 } bool;

#define SNAKE_HEAD 'H'
#define SNAKE_BODY 'X'
#define MAP_SPACE ' '
#define MAP_WALL '*'
#define FOOD '$'

#define MAX_WIDTH 30
#define MAX_HEIGHT 30

char map[MAX_WIDTH][MAX_HEIGHT];
int food_x;
int food_y;
bool is_init_seed_random = false;

struct list{
    struct node * head;
    int length;
    int last_x;
    int last_y;
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

static struct termios ori_attr, cur_attr;

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
bool OppositeDirect(InputKey a, InputKey b);


/**********************************************************************************
 *  Function about List
 **********************************************************************************/
void InitList(List* l);
void AddNodeAtHead(List l, int x, int y);
bool DeleteNodeAtLast(List l);
void DeleteList(List* l);


/**********************************************************************************
 *  Function about POSIX
 **********************************************************************************/
void clearscreen();
int kbhit();
int tty_set();
int tty_reset();

#endif /* SNAKE_H_ */
