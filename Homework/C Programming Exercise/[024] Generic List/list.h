/*
 * list.h
 *
 *  Created on: Oct 22, 2015
 *      Author: Jiaqi Ye
 */

#include <stdio.h>

#ifndef BOOLEAN
#define BOOLEAN
typedef enum {true = 1, false = 0} bool;
#endif

#ifndef LIST_H_
#define LIST_H_
struct node {
    void * data;
    struct node* next;
};

struct list {
    // the head node of the list
    struct node * head;
    // the data size of each element in the list
    int data_size;
    // the size of the list
    int length;
};

#ifndef NODE_SIZE
#define NODE_SIZE sizeof(struct node)
#endif // NODE_SIZE
#ifndef LIST_SIZE
#define LIST_SIZE sizeof(struct list)
#endif // LIST_SIZE

// Poniter for struct node
typedef struct node* Iterator;

// Pointer for struct list
typedef struct list* List;


/*
    InitList
    @function: Initialize a list with the given data size
    @param: List * list indicates the list pointer's pointer
            int datasize indicates the datasize for each element in the list
    @return: if the operation is success return true, else retuen false
*/
bool InitList(List *list, int data_size);

/*
    Append
    @function: set a new node to the end of the list
    @param: List * list indicates the list pointer's pointer
            void * data indicates the generic data
            bool(*assign)(void *, void *) indicates a function pointer to provide assign rule for the data
    @return: if the operation is success return true, else retuen false
*/
bool Append(List list, void * data, bool(*assign)(void *, void *));

/*
    AppendAt
    @function: set a new node after the index of the list
    @param: List * list indicates the list pointer's pointer
            int index indicates the index to be inserted data
            void * data indicates the generic data
            bool(*assign)(void *, void *) indicates a function pointer to provide assign rule for the data
    @return: if the operation is success return true, else retuen false
*/
bool AppendAt(List list, int index, void * data, bool(*assign)(void *, void *));

/*
    Remove
    @function: remove a node of the list
    @param: List * list indicates the list pointer's pointer
            void * data indicates the generic data to be deleted
            bool(*equal)(const void*, const void *) is a function poniter indicates the rule of "equal"
    @return: if the operation is success return true, else retuen false
*/
bool Remove(List list, void *data, bool(*equal)(const void*, const void *));

/*
    RemoveAt
    @function: remove a node of the list using index
    @param: List * list indicates the list pointer's pointer
            int index indicates the index of element to be deleted
    @return: if the operation is success return true, else retuen false
*/
bool RemoveAt(List list, int index);

/*
    traversal
    @function: traversal with an operation rule
    @param: List * list indicates the list pointer's pointer
            filter is a function indicates the rule for which elements should be updated
            operation is a function to apply actions on the elements
    @return: A list with result
*/
bool traversal(const List list, bool(*filter)(const void *), bool(*operation)(const void *));

/*
    DeleteList
    @function: deconstuct the list deleting all the elements
    @param: a list
*/
bool DeleteList(List *list);


#endif /* LIST_H_ */
