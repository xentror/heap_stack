#include "heap-stack-tests.h"
#include "../heap-stack-helpers.h"

int_array_t create_simple_int_array(int len)
{
    int *res = stack_malloc(len * sizeof(int));
    static __thread int occ;
    static __thread int nb_array = 1;
    int_array_t array;

    memset(&array, 0, sizeof(int_array_t));
    if (res == NULL) {
        return array;
    }

    for (int i = 0; i < len; i++) {
        res[i] = occ++;
    }
    tid_printf("create array %d, len: %d\n", nb_array, len);

    array.tab = res;
    array.len = len;
    array.id = nb_array++;
    return array;
}

void print_int_array(int_array_t array, int len)
{
    tid_printf("Array %d, len %d: [", array.id, len);
    for (int i = 0; i < len; i++) {
        printf("%d,", array.tab[i]);
    }
    puts("];");
}

int main(void)
{
    if (test_1() < 0) {
        return -1;
    } else
    if (test_2() < 0) {
        return -1;
    }
    return 0;
}
