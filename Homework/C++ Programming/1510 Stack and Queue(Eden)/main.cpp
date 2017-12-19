// Written by Matrix
#include <stdio.h>
#include "stack.hpp"
#include "queue.hpp"

void test_stack(void) {
  if (true) {
    stack st;
    for (int i = 0; i < 5; i++) {
      st.push(i);
    }
    st.isEmpty() ? printf("empty\n") : printf("not empty\n");
    st.isFull() ? printf("full\n") : printf("not full\n");
    for (int i = 0; i < 5; i++) {
      printf("%d ", st.peek());
      st.pop();
    }
    printf("\n");
    st.isEmpty() ? printf("empty\n") : printf("not empty\n");
    st.isFull() ? printf("full\n") : printf("not full\n");
  }

  printf("\n");

  if (true) {
    stack st;
    for (int i = 0; i < 11; i++) {
      st.push(i);
    }
    st.isEmpty() ? printf("empty\n") : printf("not empty\n");
    st.isFull() ? printf("full\n") : printf("not full\n");
    for (int i = 0; i < 10; i++) {
      printf("%d ", st.peek());
      st.pop();
    }
    printf("\n");
    st.isEmpty() ? printf("empty\n") : printf("not empty\n");
    st.isFull() ? printf("full\n") : printf("not full\n");
  }

  printf("\n");

  if (true) {
    stack st;
    for (int i = 0; i < 20; i++) {
      st.push(i);
    }
    st.clear();
    st.isEmpty() ? printf("empty\n") : printf("not empty\n");
    st.isFull() ? printf("full\n") : printf("not full\n");
    for (int i = 0; i < 11; i++) {
      st.push(i);
    }
    st.isEmpty() ? printf("empty\n") : printf("not empty\n");
    st.isFull() ? printf("full\n") : printf("not full\n");
    for (int i = 0; i < 10; i++) {
      printf("%d ", st.peek());
      st.pop();
    }
    printf("\n");
    st.isEmpty() ? printf("empty\n") : printf("not empty\n");
    st.isFull() ? printf("full\n") : printf("not full\n");
  }
}

void test_queue(void) {
  if (true) {
    queue qu;
    for (int i = 0; i < 5; i++) {
      qu.push(i);
    }
    qu.isEmpty() ? printf("empty\n") : printf("not empty\n");
    qu.isFull() ? printf("full\n") : printf("not full\n");
    for (int i = 0; i < 5; i++) {
      printf("(%d,%d) ", qu.front(), qu.back());
      qu.pop();
    }
    printf("\n");
    qu.isEmpty() ? printf("empty\n") : printf("not empty\n");
    qu.isFull() ? printf("full\n") : printf("not full\n");
  }
  printf("\n");

  if (true) {
    queue qu;
    for (int i = 0; i < 11; i++) {
      qu.push(i);
    }
    qu.isEmpty() ? printf("empty\n") : printf("not empty\n");
    qu.isFull() ? printf("full\n") : printf("not full\n");
    for (int i = 0; i < 11; i++) {
      printf("(%d,%d) ", qu.front(), qu.back());
      qu.pop();
    }
    printf("\n");
    qu.isEmpty() ? printf("empty\n") : printf("not empty\n");
    qu.isFull() ? printf("full\n") : printf("not full\n");
  }

  printf("\n");

  if (true) {
    queue qu;
    for (int i = 0; i < 11; i++) {
      qu.push(i);
    }
    qu.isEmpty() ? printf("empty\n") : printf("not empty\n");
    qu.isFull() ? printf("full\n") : printf("not full\n");
    qu.clear();
    qu.isEmpty() ? printf("empty\n") : printf("not empty\n");
    qu.isFull() ? printf("full\n") : printf("not full\n");
    for (int i = 0; i < 5; i++) {
      qu.push(i);
    }
    for (int i = 0; i < 5; i++) {
      printf("(%d,%d) ", qu.front(), qu.back());
      qu.pop();
    }
    printf("\n");
    qu.isEmpty() ? printf("empty\n") : printf("not empty\n");
    qu.isFull() ? printf("full\n") : printf("not full\n");
  }

  printf("\n");
}

int main() {
  test_stack();
  test_queue();
  return 0;
}
 
