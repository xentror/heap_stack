#include "generic-list.h"

#include <stdio.h>

typedef struct integ_list {
    int value;
    node_t node;
} integ_list_t;


void print_integ_list(integ_list_t *list) {
    printf("list: ");

    while (list) {
        printf("%d ", list->value);
        list = glist_get_next_node(integ_list_t, list);
    }

    puts("");
}

int main(void)
{
    integ_list_t *l = glist_create(integ_list_t);

    l = glist_add_node(integ_list_t, l, 0);
    l = glist_add_node(integ_list_t, l, 0);

    print_integ_list(l);

    l = glist_delete_node(integ_list_t, l, 1);
    print_integ_list(l);
    l = glist_delete_node(integ_list_t, l, 1);
    print_integ_list(l);
    l = glist_delete_node(integ_list_t, l, 0);
    print_integ_list(l);


    l = glist_add_node(integ_list_t, l, 0);
    print_integ_list(l);

    glist_erase(integ_list_t, &l);
    print_integ_list(l);

    return 0;
}
