/* Written by Matrix */

#include "list.h"
#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct my_data {
  int data_int;
  double data_double;
  char data_string[100];
};

bool assign_int(void * x, void * y) {
  *((int *)x) = *((int *)y);
  return true;
}

bool assign_double(void * x, void * y) {
  *((double *) x) = *((double *)y);
  return true;
}

bool assign_struct(void * x, void * y) {
  struct my_data * data_x = (struct my_data *) x;
  struct my_data * data_y = (struct my_data *) y;
  data_x->data_int = data_y->data_int;
  data_x->data_double = data_y->data_double;
  strncpy(data_x->data_string, data_y->data_string, 100);
}

bool equal_int(const void * x, const void * y) {
  return *((int *)x) == *((int *)y);
}

bool equal_double(const void * x, const void * y) {
  double diff = *((double *)x) - *((double *)y);
  return diff > 0 ? diff < 0.000001 : diff > -0.000001;
}

bool equal_struct(const void * x, const void * y) {
  struct my_data * data_x = (struct my_data *) x;
  struct my_data * data_y = (struct my_data *) y;
  if(data_x->data_int != data_y->data_int) {
    return false;
  }
  if(!equal_double((void *)(&(data_x->data_double)), (void *)(&(data_y->data_double)))) {
    return false;
  }
  return strcmp(data_x->data_string, data_y->data_string) == 0;
}

bool filter_all(const void * x) {
  return true;
}

bool filter_odd(const void * x) {
  return *((int *)x) & 1;
}

bool filter_even(const void * x) {
  return !(*((int*)x) & 1);
}

bool operation_print_int(const void * x) {
  printf("%d->", *((int *)x));
}

bool operation_print_double(const void * x) {
  printf("%lf->", *((double *)x));
}

bool operation_print_struct(const void * x) {
  struct my_data * data = (struct my_data *)x;
  printf("{'int':%d, 'double':%lf, 'string':%s}->",
                                        data->data_int,
                                        data->data_double,
                                        data->data_string
                                      );
}

void test0(int * data, int size) {
  List l = (List)malloc(LIST_SIZE);
  InitList(&l, sizeof(int));

  for(int i =0; i < size; i++) {
    Append(l, data + i, assign_int);
  }

  RemoveAt(l, -1);

  traversal(l, filter_all, operation_print_int); printf("\n");

  traversal(l, filter_odd, operation_print_int); printf("\n");

  traversal(l, filter_even, operation_print_int); printf("\n");

  DeleteList(&l);
  free(l);
}

void test1(double * data, int size) {
  List l = (List)malloc(LIST_SIZE);
  InitList(&l, sizeof(double));
  // append all
  for(int i = 0; i < size; i++) {
    Append(l, data + i, assign_double);
  }

  traversal(l, filter_all, operation_print_double);
  printf("\n");

  for(int i = -2; i < size + 2; i++) {
    RemoveAt(l, i);
  }
  traversal(l, filter_all, operation_print_double);
  printf("\n");

  for(int i = 0; i < size; i++) {
    Remove(l, data + i, equal_double);
  }
  traversal(l, filter_all, operation_print_double);
  printf("\n");

  DeleteList(&l);
  free(l);
}

void test2(struct my_data * data, int size) {
  List l = (List)malloc(LIST_SIZE);
  InitList(&l, sizeof(struct my_data));
  // append all
  for(int i = 0; i < size; i++) {
    Append(l, data + i, assign_struct);
  }

  traversal(l, filter_all, operation_print_struct);
  printf("\n");

  for(int i = -2; i < size + 2; i++) {
    RemoveAt(l, i);
  }
  traversal(l, filter_all, operation_print_struct);
  printf("\n");

  for(int i = 0; i < size; i++) {
    Remove(l, data + i, equal_struct);
  }
  traversal(l, filter_all, operation_print_struct);
  printf("\n");

  DeleteList(&l);
  free(l);
}

int main() {
  int size1 = 0, size2 = 0, size3 = 0, size4 = 0;
  int data_set1[1000] = {0};
  double data_set2[1000] = {0};
  struct my_data data_set3[1000];
  int index_set[1000] = {3};

  scanf("%d%d%d%d", &size1, &size2, &size3, &size4);

  for(int i = 0; i < size1; i++) {
    scanf("%d", &data_set1[i]);
  }

  for(int i = 0; i < size2; i++) {
    scanf("%lf", &data_set2[i]);
  }

  for(int i = 0; i < size3; i++) {
    scanf("%d %lf %s", &(data_set3[i].data_int), &(data_set3[i].data_double), data_set3[i].data_string);
  }

  for(int i = 0; i < size4; i++) {
    scanf("%d", &index_set[i]);
  }

  test0(data_set1, size1);
  test1(data_set2, size2);
  test2(data_set3, size3);

  return 0;
}
