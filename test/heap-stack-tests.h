#ifndef HEAP_STACK_TESTS
#define HEAP_STACK_TESTS

#include "../heap-stack.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct int_array_t {
    int *tab;
    int len;
    int id;
} int_array_t;

int_array_t create_simple_int_array(int len);
void print_int_array(int_array_t array, int len);

int test_2(void);
int test_1(void);

#endif
