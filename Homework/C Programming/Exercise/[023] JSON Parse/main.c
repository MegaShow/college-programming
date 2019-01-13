/* Written by Matrix */

#include <stdio.h>
#include "json_parse.h"

int main() {
  char json_str[MAX_SIZE + 1] = {0};
  scanf("%s", json_str);
  if (jsonParse(json_str) == FAILED)
    printf("ERROR!\n");

  return 0;
}

/* Functions definition */

void TokenStack_init(TokenStack *stack) {
  memset(stack, 0, sizeof(stack->stack_storage));
  stack->top_ptr = -1;
}

Boolean TokenStack_empty(TokenStack *stack) {
  if (stack->top_ptr == -1) {
    return true;
  } else {
    return false;
  }
}

TokenType TokenStack_top(TokenStack *stack) {
  if (!TokenStack_empty(stack)) {
    return stack->stack_storage[stack->top_ptr];
  }
  return ERR;
}

ErrCode TokenStack_pop(TokenStack *stack) {
  if (TokenStack_empty(stack)) {
    return FAILED;
  } else {
    (stack->top_ptr)--;
    return SUCCESS;
  }
}

ErrCode TokenStack_push(TokenStack *stack, TokenType val) {
  if (stack->top_ptr + 1 > MAX_SIZE) {
    return FAILED;
  }
  stack->stack_storage[++(stack->top_ptr)] = val;
  return SUCCESS;
}

Boolean has_status(Status now_status, Status status) {
  if ((now_status & status) == status)
    return true;
  return false;
}

void printIndent(int times) {
  while (times--) {
    printf(" ");
  }
}

void printKey() {
  printf("KEY: ");
}

void printNumber(Number num) {
  printf("NUMBER: %lf\n", num);
}

void printBoolean(Boolean boo) {
  if (boo) {
    printf("BOOLEAN: true\n");
  } else {
    printf("BOOLEAN: false\n");
  }
}

void printNull() {
  printf("Null: null\n");
}

void printString(String sub_str) {
  char str[MAX_SIZE] = {0};
  strncpy(str, sub_str.begin, sub_str.end - sub_str.begin + 1);
  printf("String: %s\n", str);
}

void printObject() {
  printf("Object:\n");
}

void printArray() {
  printf("Array:\n");
}

/* End */
