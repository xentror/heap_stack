#include "linked-list.h"

#include <stddef.h>
#include <stdlib.h>

typedef struct node_t {
    node_t *next;
    node_t *prev;
} node_t;


node_t* create_node()
{
    node_t *res = malloc(sizeof(node_t));

    res->prev = NULL;
    res->next = NULL;

    return res;
}

node_t* get_next_node(node_t *node)
{
    if (!node) {
        return NULL;
    }

    return node->next;
}

node_t* get_prev_node(node_t *node)
{
    if (!node) {
        return NULL;
    }

    return node->prev;
}

node_t* delete_node(node_t *node, unsigned int n)
{
    node_t *tmp = node;
    unsigned int cpt = 0;

    if (!tmp)
        return NULL;

    if (n == 0) {
        node = node->next;

        if (node)
            node->prev = NULL;
        free(tmp);

        return node;
    }

    while (tmp->next && cpt < n) {
        tmp = tmp->next;
        cpt++;
    }

    if (cpt != n)
        return node;

    if (tmp->prev)
        tmp->prev->next = tmp->next;
    if (tmp->next)
        tmp->next->prev = tmp->prev;
    free(tmp);

    return node;
}

node_t* add_node(node_t *node, unsigned int n)
{
    node_t *tmp = node;
    unsigned int cpt = 0;
    node_t *new_node = NULL;

    if (!tmp)
        return create_node();

    if (n == 0) {
        tmp = tmp->next;
        node = create_node();
        node->next = tmp;

        return node;
    }

    while (tmp->next && cpt < n) {
        tmp = tmp->next;
        cpt++;
    }

    if (cpt != n)
        return node;

    new_node = create_node();
    new_node->next = tmp;
    new_node->prev = tmp->prev;

    if (tmp->prev)
        tmp->prev->next = new_node;
    tmp->prev = new_node;

    return node;
}

unsigned int get_size_list(node_t* node)
{
    unsigned int res = 0;

    while (node) {
        node = node->next;
        res++;
    }

    return res;
}
