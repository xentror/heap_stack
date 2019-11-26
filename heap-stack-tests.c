#include "heap-stack.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct int_array_t {
    int *tab;
    int len;
    int id;
} int_array_t;

static int_array_t create_simple_int_array(int len)
{
    int *res = stack_malloc(len * sizeof(int));
    static int occ;
    static int nb_array = 1;
    int_array_t array;

    memset(&array, 0, sizeof(int_array_t));
    if (res == NULL) {
        return array;
    }

    for (int i = 0; i < len; i++) {
        res[i] = occ++;
    }
    printf("create array %d, len: %d\n", nb_array, len);

    array.tab = res;
    array.len = len;
    array.id = nb_array++;
    return array;
}

void print_int_array(int_array_t array, int len)
{
    printf("Array %d, len %d: [", array.id, len);
    for (int i = 0; i < len; i++) {
        printf("%d,", array.tab[i]);
    }
    puts("];");
}

static int foo_2(int_array_t array, int len)
{
    stack_scope;

    print_int_array(array, len);
    return -1;
}

static int foo_3(void)
{
    stack_scope;
    int_array_t array = create_simple_int_array(5);
    int_array_t array_2 = create_simple_int_array(5);

    array_2.tab[0] = array_2.tab[0];

    print_int_array(array, 10);
    return 0;
}

static int_array_t foo_4(int len)
{
    stack_scope;
    int_array_t array = create_simple_int_array(len);

    print_int_array(array, len);
    return array;
}

static int foo_1(void)
{
    stack_scope;
    int_array_t array_3 = create_simple_int_array(5);
    int_array_t array_4;

    if (array_3.len == 0) {
        return -1;
    }
    foo_2(array_3, 5);
    foo_3();
    array_4 = foo_4(5);
    foo_4(5);

    print_int_array(array_4, 5);

    /* overwrite the canary: should assert */
    //array_3.tab[-1] = 0;
    return 0;
}

int main(void)
{
    stack_scope;
    int_array_t array_1 = create_simple_int_array(10);
    int_array_t array_2 = create_simple_int_array(10);

    if (array_1.len == 0 || array_2.len == 0) {
        return -1;
    }

    foo_1();
    print_int_array(array_1, 10);
    print_int_array(array_2, 10);
    return 0;
}
