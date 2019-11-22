#include "heap-stack.h"

#include <stdio.h>

static int *create_simple_int_array(int len)
{
    int *res = stack_malloc(len * sizeof(int));
    static int occ;

    if (res == NULL) {
        return NULL;
    }

    for (int i = 0; i < len; i++) {
        res[i] = occ++;
    }
    return res;
}

void print_int_array(int *array, int len)
{
    printf("array: [");
    for (int i = 0; i < len; i++) {
        printf("%d,", array[i]);
    }
    puts("];");
}

static int foo_2(int *array, int len)
{
    stack_scope;

    print_int_array(array, len);
    return -1;
}

static int foo_3(void)
{
    stack_scope;
    int *array = create_simple_int_array(5);
    int *array_2 = create_simple_int_array(5);

    array_2[0] = array_2[0];
    print_int_array(array, 10);
    return 0;
}

static int foo_1(void)
{
    stack_scope;
    int *array = create_simple_int_array(5);

    if (array == NULL) {
        return -1;
    }
    foo_2(array, 5);
    foo_3();
    print_int_array(array, 5);
    return 0;
}

int main(void)
{
    stack_scope;
    int *array = create_simple_int_array(10);
    int *array_2 = create_simple_int_array(10);

    if (array == NULL || array_2 == NULL) {
        return -1;
    }

    foo_1();
    print_int_array(array, 10);
    print_int_array(array_2, 10);
    return 0;
}
