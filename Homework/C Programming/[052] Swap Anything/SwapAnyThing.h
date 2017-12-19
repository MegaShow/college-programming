/*
 *	Name: [052] Swap Anything
 *	Author: Mega Show
 *	Date: 2016.12.6
 */
 
#ifndef SWAPANYTHING_H
#define SWAPANYTHING_H

#include <stdlib.h>

void swapAnyThing(void *a, void *b, size_t val_size){
	void* ptr = malloc(val_size);
	memcpy(ptr, a, val_size);
	memcpy(a, b, val_size);
	memcpy(b, ptr, val_size);
	free(ptr);
}

#endif