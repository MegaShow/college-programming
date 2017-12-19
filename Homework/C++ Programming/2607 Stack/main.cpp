#include <stdio.h>
#include "stack.hpp"

void test_stack(void) {
  if (true) {
    stack st;
    for (int i = 0; i < 5; i++) {
      st.push(i);
    }
    st.isEmpty() ? printf("empty\n") : printf("not empty\n");
    st.isFull() ? printf("full\n") : printf("not full\n");
    for (int i = 0; i < 5; i++) {
      printf("%d ", st.top());
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
      printf("%d ", st.top());
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
      printf("%d ", st.top());
      st.pop();
    }
    printf("\n");
    st.isEmpty() ? printf("empty\n") : printf("not empty\n");
    st.isFull() ? printf("full\n") : printf("not full\n");
  }
}

int main() {
  test_stack();
  return 0;
}
