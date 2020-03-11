#include "generic-list.h"

#include <assert.h>
#include <stdio.h>

typedef struct integ_list {
    int size;
    int *values;
    node_t node;
} integ_list_t;

integ_list_t* integ_list_init()
{
    integ_list_t *list = calloc(10, sizeof(integ_list_t));

    if (!list)
        return NULL;

    list->values = calloc(2, sizeof(int));
    list->size = 2;

    if (!list->values)
        return NULL;

    return list;
}

void integ_list_destroy(integ_list_t *list)
{
    free(list->values);
    free(list);
}

GLIST_INIT(integ_list, integ_list_init, integ_list_destroy)

void print_integ_list(integ_list_t *list)
{
    int i = 0;

    printf("{ ");
    for (; i < list->size - 1; i++)
        printf("%d,", list->values[i]);
    printf("%d }", list->values[i]);
}

void push_and_pop()
{
    integ_list_t *l = integ_list_create();
    l->values[0] = -1;
    l->values[1] = -1;

    for (int i = 0; i < 10; i++) {
        integ_list_t *tmp_node = integ_list_create();

        if (!tmp_node)
            return;

        tmp_node->values[0] = i;
        l = integ_list_push(l, tmp_node);
    }

    assert (integ_list_get_size(l) == 11);

    integ_list_print(l, print_integ_list);

    for (int i = 0; i < 11; i++) {
        l = integ_list_pop(l);
        integ_list_print(l, print_integ_list);
    }

    assert (l == NULL);
    assert (integ_list_get_size(l) == 0);
}

void insert_and_delete_front()
{
    integ_list_t *new_node = NULL;
    integ_list_t *l = integ_list_create();
    l->values[0] = -1;
    l->values[1] = -1;

    for (int i = 0; i < 10; i++) {
        new_node = integ_list_create();
        new_node->values[0] = i;
        l = integ_list_insert_at(l, new_node, 0);
    }
    integ_list_print(l, print_integ_list);

    for (int i = 0; i < 10; i++) {
        l = integ_list_delete_at(l, 0);
        integ_list_print(l, print_integ_list);
    }
    integ_list_print(l, print_integ_list);

    integ_list_erase(&l);
    assert (l == NULL);
    assert (integ_list_get_size(l) == 0);
}

void insert_delete_middle()
{
    integ_list_t *new_node = NULL;
    integ_list_t *l = integ_list_create();
    l->values[0] = -1;
    l->values[1] = -1;

    new_node = integ_list_create();
    new_node->values[0] = 0;
    l = integ_list_push(l, new_node);

    new_node = integ_list_create();
    new_node->values[0] = 2;
    l = integ_list_push(l, new_node);

    new_node = integ_list_create();
    new_node->values[0] = 1;
    l = integ_list_insert_at(l, new_node, 2);

    integ_list_print(l, print_integ_list);

    l = integ_list_delete_at(l, 2);
    integ_list_print(l, print_integ_list);

    integ_list_erase(&l);
    assert (l == NULL);
    assert (integ_list_get_size(l) == 0);
}

int main(void)
{
    push_and_pop();
    insert_and_delete_front();
    insert_delete_middle();

    return 0;
}
