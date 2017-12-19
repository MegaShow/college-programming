/*
 *	Name: [024] Generic List
 *	Author: Mega Show
 *	Date: 2016.12.24
 */

#include <stdlib.h>
#include "list.h"


/*
    InitList
    @function: Initialize a list with the given data size
    @param: List * list indicates the list pointer's pointer
            int datasize indicates the datasize for each element in the list
    @return: if the operation is success return true, else retuen false
*/
bool InitList(List *list, int data_size){
    (*list)->head = NULL;
    (*list)->data_size = data_size;
    (*list)->length = 0;
    return true;
}


/*
    Append
    @function: set a new node to the end of the list
    @param: List * list indicates the list pointer's pointer
            void * data indicates the generic data
            bool(*assign)(void *, void *) indicates a function pointer to provide assign rule for the data
    @return: if the operation is success return true, else retuen false
*/
bool Append(List list, void * data, bool(*assign)(void *, void *)){
    Iterator new_node = (Iterator)malloc(NODE_SIZE);
    new_node->data = malloc(list->data_size);
    assign(new_node->data, data);
    new_node->next = NULL;
    if(list->head == NULL){
        list->head = new_node;
        list->length += 1;
        return true;
    }
    else{
        Iterator n = list->head;
        while(n->next != NULL)
            n = n->next;
        n->next = new_node;
        list->length += 1;
        return true;
    }
}


/*
    AppendAt
    @function: set a new node after the index of the list
    @param: List * list indicates the list pointer's pointer
            int index indicates the index to be inserted data
            void * data indicates the generic data
            bool(*assign)(void *, void *) indicates a function pointer to provide assign rule for the data
    @return: if the operation is success return true, else retuen false
*/
bool AppendAt(List list, int index, void * data, bool(*assign)(void *, void *)){
    if(index < 0 || index > list->length)
        return false;
    Iterator new_node = (Iterator)malloc(NODE_SIZE);
    new_node->data = malloc(list->data_size);
    assign(new_node->data, data);
    if(index == 0){
        new_node->next = list->head;
        list->head = new_node;
        list->length += 1;
        return true;
    }
    else if(index == 1){
        new_node->next = list->head->next;
        list->head->next = new_node;
        list->length += 1;
        return true;
    }
    else{
        Iterator n = list->head;
        for(int i = 2; i <= index; i++)
            n = n->next;
        new_node->next = n->next->next;
        n->next = new_node;
        list->length += 1;
        return true;
    }
}


/*
    Remove
    @function: remove a node of the list
    @param: List * list indicates the list pointer's pointer
            void * data indicates the generic data to be deleted
            bool(*equal)(const void*, const void *) is a function poniter indicates the rule of "equal"
    @return: if the operation is success return true, else retuen false
*/
bool Remove(List list, void *data, bool(*equal)(const void*, const void *)){
    if(list->head == NULL)
        return false;
    if(equal(list->head->data, data)){
        Iterator n = list->head->next;
        free(list->head->data);
        free(list->head);
        list->head = n;
        list->length -= 1;
        return true;
    }
    else{
        Iterator prev = list->head;
        Iterator n = prev->next;
        Iterator temp;
        while(n != NULL){
            if(equal(n->data, data)){
                temp = n->next;
                free(n->data);
                free(n);
                prev->next = temp;
                list->length -= 1;
                return true;
            }
            else{
                prev = n;
                n = n->next;
            }
        }
    }
    return false;
}


/*
    RemoveAt
    @function: remove a node of the list using index
    @param: List * list indicates the list pointer's pointer
            int index indicates the index of element to be deleted
    @return: if the operation is success return true, else retuen false
*/
bool RemoveAt(List list, int index){
    if(index < 0 || index >= list->length)
        return false;
    Iterator n = list->head;
    Iterator prev = list->head;
    if(index == 0){
        n = n->next;
        free(list->head);
        list->head = n;
        list->length -= 1;
        return true;
    }
    for(int i = 2; i <= index; i++)
        prev = prev->next;
    n = prev->next;
    prev->next = n->next;
    free(n);
    list->length -= 1;
    return true;
}


/*
    traversal
    @function: traversal with an operation rule
    @param: List * list indicates the list pointer's pointer
            filter is a function indicates the rule for which elements should be updated
            operation is a function to apply actions on the elements
    @return: A list with result
*/
bool traversal(const List list, bool(*filter)(const void *), bool(*operation)(const void *)){
    Iterator n = list->head;
    while(n != NULL){
        if(filter(n->data)){
            operation(n->data);
        }
        n = n->next;
    }
}


/*
    DeleteList
    @function: deconstuct the list deleting all the elements
    @param: a list
*/
bool DeleteList(List *list){
    Iterator n = (*list)->head;
    Iterator temp;
    while(n != NULL){
        temp = n->next;
        free(n->data);
        free(n);
        n = temp;
    }
}
