#include "generic-list.h"

#include <assert.h>
#include <stdio.h>

typedef struct integ_list {
    int value;
    node_t node;
} integ_list_t;


void print_integ_list(integ_list_t *list)
{
    printf("%d", list->value);
}

int main(void)
{
    integ_list_t *new_node = NULL;
    integ_list_t *l = glist_create(integ_list_t);
    l->value = -1;

    for (int i = 0; i < 10; i++) {
        integ_list_t *tmp_node = glist_create(integ_list_t);

        if (!tmp_node)
            return 1;

        tmp_node->value = i;
        l = glist_add_node(integ_list_t, l, tmp_node, 0);
    }

    assert (glist_get_size(integ_list_t , l) == 11);

    glist_print(integ_list_t, l, print_integ_list);

    l = glist_delete_node(integ_list_t, l, 1);
    glist_print(integ_list_t, l, print_integ_list);
    l = glist_delete_node(integ_list_t, l, 1);
    glist_print(integ_list_t, l, print_integ_list);
    l = glist_delete_node(integ_list_t, l, 0);
    glist_print(integ_list_t, l, print_integ_list);

    assert (glist_get_size(integ_list_t, l) == 8);

    new_node = glist_create(integ_list_t);
    new_node->value = 678;
    l = glist_add_node(integ_list_t, l, new_node, 0);
    glist_print(integ_list_t, l, print_integ_list);

    glist_erase(integ_list_t, &l);
    glist_print(integ_list_t, l, print_integ_list);

    assert (l == NULL);
    assert (glist_get_size(integ_list_t, l) == 0);
    return 0;
}
