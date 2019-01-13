#ifndef BUFFER_H_
#define BUFFER_H_

#define BUFFER_SIZE 5

typedef int bufferItem;

int insertItem(bufferItem item);
int removeItem(bufferItem* item);

#endif
