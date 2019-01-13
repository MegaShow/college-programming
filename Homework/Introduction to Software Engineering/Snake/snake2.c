/*
 *	Name: snake2.c
 *	Author: Mega Show
 *	Date: 2016.12.19
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "snake2.h"


/**********************************************************************************
 *   main
 *  @function: the main function
 **********************************************************************************/
/*
# main()
创建链表snake
执行map和snake的初始化
WHILE snake_is_alive
    输入操作
    IF 输入错误
        输出错误信息
    ELSE
        移动snake
        判断snake是否死亡
        IF snake_is_alive
            更新map信息
            输出map
        END IF
    END IF
END WHILE
输出游戏结束信息
删除链表snake
*/
int main(){
    Player snake;
    InputKey input;
    bool is_alive = true;
    CreateNewGame(&snake);
    while(is_alive){
        input = GetInput();
        if(input == ERROR){
            printf("Invalid Input!!!\n");
            continue;
        }
        is_alive = MovePlayer(snake, input);
        if(is_alive){
            UpdateMap(snake);
            DrawMap();
        }
        if(is_alive == eof)
            break;
    }
    GameOver(&snake, is_alive);
    return 0;
}

/**********************************************************************************
 *   CreateNewGame
 *  @function: Create a 5-length snake.
 *  @param: Player* means the list of snake's pointer's pointer
 *          Player* <=> List* <=> list**
 **********************************************************************************/
/*
# CreateNewGame()
初始化链表
创建游戏开始的snake
更新map信息
输出map
*/
void CreateNewGame(Player* l){
    InitList(l);
    for(int x = 1; x <= 5; x++)
        AddNodeAtHead(*l, x, 1);
    UpdateMap(*l);
    CreateRandomFood(*l);
    UpdateMap(*l);
    DrawMap();
}

/**********************************************************************************
 *   CreateRandomFood
 *  @function: Get a food position
 *  @param: Player l : list's pointer
 *  @return: when win the game, it returns false
 **********************************************************************************/
bool CreateRandomFood(Player l){
    if(is_init_seed_random != true){
        srand(time(NULL));
        is_init_seed_random = true;
    }
    if(l->length == width * height)
        return false;
    while(map[food_x][food_y] != MAP_SPACE){
        food_x = rand() % width + 1;
        food_y = rand() % height + 1;
        bool flag = false;
        for(int y = 1; y <= height; y++){
            if(map[food_x][y] == MAP_SPACE)
                flag = true;
        }
        while(flag && map[food_x][food_y] != MAP_SPACE)
            food_y = rand() % height + 1;
    }
    return true;
}

/**********************************************************************************
 *   GetInput
 *  @function: Get a input from function scanf
 *  @return: InputKey
 **********************************************************************************/
/*
# GetInput()
c = 输入字符
CASE c DO
    'w' : 确认状态为向上移动
    's' : 确认状态为向下移动
    'a' : 确认状态为向左移动
    'd' : 确认状态为向右移动
    otherwise : 输入信息非法
END CASE
return snake状态
*/
InputKey GetInput(){
    char c;
    scanf("%c", &c);
    while(c == '\n'){
        scanf("%c", &c);
    }
    switch(c){
        case 'w': return UP;
        case 's': return DOWN;
        case 'a': return LEFT;
        case 'd': return RIGHT;
        default:  return ERROR;
    }
}

/**********************************************************************************
 *   MovePlayer
 *  @function: Change the list of snake
 *  @param: Player l is the list of snake 's pointer
 *  @param: InputKey input get from function GetInput,
 *          it won't be the enum value "ERROR"
 *  @return: when it return false, it means snake is dead or invalid.
 **********************************************************************************/
/*
# MovePlayer()
获取snake头部坐标
通过状态得到snake头部的新坐标
判断snake是否死亡
IF is_alive
    新坐标有效
    在链表头部增加新坐标
    删除链表最后一个元素
END IF
*/
bool MovePlayer(Player l, InputKey input){
    if(l->head == NULL)
        return false;
    int x = l->head->x;
    int y = l->head->y;
    switch(input){
        case UP: y--; break;
        case DOWN: y++; break;
        case LEFT: x--; break;
        case RIGHT: x++; break;
    }
    if(map[x][y] == MAP_WALL || map[x][y] == SNAKE_BODY)
        return false;
    AddNodeAtHead(l, x, y);
    if(map[x][y] == FOOD){
        bool is_get_food_success = CreateRandomFood(l);
        if(is_get_food_success == false)
            return eof;
    }
    else
        DeleteNodeAtLast(l);
    return true;
}

/**********************************************************************************
 *   UpdateMap
 *  @function: Update the 2d char variable "map"
 *  @param: Player l is the list of snake 's pointer
 **********************************************************************************/
/*
# UpdateMap()
初始化map背景
将链表每一个元素赋值到map上面
*/
void UpdateMap(Player l){
    memset(map, MAP_SPACE, sizeof(map));
    for(int x = 0; x <= width + 1; x++)
        map[x][0] = map[x][height+1] = MAP_WALL;
    for(int y = 1; y <= height; y++)
        map[0][y] = map[width+1][y] = MAP_WALL;
    Node n = l->head;
    if(n != NULL)
        map[n->x][n->y] = SNAKE_HEAD;
    for(int i = 1; i < l->length; i++){
        n = n->next;
        map[n->x][n->y] = SNAKE_BODY;
    }
    map[food_x][food_y] = FOOD;
}

/**********************************************************************************
 *   DrawMap
 *  @function: Print map in the screen
 **********************************************************************************/
void DrawMap(){
    for(int y = 0; y <= height + 1; y++){
        for(int x = 0; x <= width + 1; x++)
            printf("%c", map[x][y]);
        printf("\n");
    }
}

/**********************************************************************************
 *   GameOver
 *  @function: Delete the list of snake
 *  @param: Player* means the list of snake's pointer's pointer
 *  @param: bool is_alive : eof means winning and false means dead
 **********************************************************************************/
void GameOver(Player* l, bool is_alive){
    if(is_alive)
        printf("You Win!!!\n");
    else
        printf("Game Over!!!\n");
    DeleteList(l);
}

/**********************************************************************************
 *   InitList
 *  @function: Create a list
 *  @param: List* l is list's pointer's pointer
 **********************************************************************************/
void InitList(List* l){
    (*l) = (List)malloc(LIST_SIZE);
    (*l)->head = NULL;
    (*l)->length = 0;
}

/**********************************************************************************
 *   AddNodeAtHead
 *  @function: insert a node at the head of list
 *  @param: List l : the list's pointer
 *  @param: int x, y : the node's variable x, y
 **********************************************************************************/
void AddNodeAtHead(List l, int x, int y){
    Node n = (Node)malloc(NODE_SIZE);
    n->next = l->head;
    n->x = x;
    n->y = y;
    l->head = n;
    l->length += 1;
}

/**********************************************************************************
 *   DeleteNodeAtLast
 *  @function: Delete a node at the last of list
 *  @param: List l : the list's pointer
 *  @return : when delete operating is failed, it returns false
 **********************************************************************************/
bool DeleteNodeAtLast(List l){
    if(l->head == NULL)
        return false;
    Node w = l->head;
    for(int i = 1; i < l->length; i++)
        w = w->next;
    free(w->next);
    w->next = NULL;
    l->length -= 1;
    return true;
}

/**********************************************************************************
 *   DeleteList
 *  @function: Clear all the list by using function free()
 *  @param: List* l : the list's pointer's pointer
 **********************************************************************************/
void DeleteList(List* l){
    Node n = (*l)->head;
    Node p;
    free(*l);
    while(n){
        p = n->next;
        free(n);
        n = p;
    }
}
