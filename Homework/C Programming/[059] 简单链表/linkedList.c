/*
 *	Name: [059] 简单链表
 *	Author: Mega Show
 *	Date: 2016.12.14
 */

#include <stdlib.h>
#include "linkedList.h"

//insert the value to the right position
//if the position is not valid, return false
//if insert successfully, return true
bool insert(int position, int value){
    if(position > size || position < 0)
        return false;
    else if(position == 0){
        node* new = (node*)malloc(sizeof(node));
        new->value = value;
        new->next = head;
        head = new;
    }
    else{
        node* p = head;
        node* t;
        for(int i = 1; i < position; i++)
            p = p->next;
        if(position != size)
            t = p->next;
        else
            t = NULL;
        node* new = (node*)malloc(sizeof(node));
        new->value = value;
        new->next = t;
        p->next = new;
    }
    size++;
    return true;
}

// return the value in the given position
int get(int position){
    node* p = head;
    for(int i = 0; i < position; i++)
        p = p->next;
    return p->value;
}

//clear the linkedlist, remember to free the memory you allocated
void clear(){
    node* p = head->next;
    node* freep;
    while(p){
        freep = p;
        p = p->next;
        free(freep);
    }
}
