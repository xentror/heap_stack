#include "generic-list.h"

#include <assert.h>
#include <stdio.h>

typedef struct integ_list {
    int value;
    node_t node;
} integ_list_t;

GLIST_INIT(integ_list)

void print_integ_list(integ_list_t *list)
{
    printf("%d", list->value);
}

int main(void)
{
    integ_list_t *new_node = NULL;
    integ_list_t *l = integ_list_create();
    l->value = -1;

    for (int i = 0; i < 10; i++) {
        integ_list_t *tmp_node = integ_list_create();

        if (!tmp_node)
            return 1;

        tmp_node->value = i;
        l = integ_list_push(l, tmp_node);
    }

    assert (integ_list_get_size(l) == 11);

    integ_list_print(l, print_integ_list);

    for (int i = 0; i < 3; i++) {
        l = integ_list_pop(l);
        integ_list_print(l, print_integ_list);
    }

    assert (integ_list_get_size(l) == 8);

    new_node = integ_list_create();
    new_node->value = 678;
    l = integ_list_push(l, new_node);
    integ_list_print(l, print_integ_list);

    integ_list_erase(&l);
    integ_list_print(l, print_integ_list);

    assert (l == NULL);
    assert (integ_list_get_size(l) == 0);
    return 0;
}
