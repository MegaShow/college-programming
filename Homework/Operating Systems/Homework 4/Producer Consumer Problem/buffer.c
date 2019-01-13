#include <pthread.h>
#include "buffer.h"

int head;
int rear;
bufferItem buffer[BUFFER_SIZE + 1];

int insertItem(bufferItem item) {
    if (head == (rear + 1) % (BUFFER_SIZE + 1)) return 1;
    buffer[rear++] = item;
    if (rear == BUFFER_SIZE + 1) rear = 0;
    return 0;
}

int removeItem(bufferItem* item) {
    if (head == rear) return 1;
    *item = buffer[head++];
    if (head == BUFFER_SIZE + 1) head = 0;
    return 0;
}
