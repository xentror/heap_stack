#ifndef GENERIC_LIST_H
#define GENERIC_LIST_H

#include "linked-list.h"

#endif

#include <stddef.h>
#include <stdlib.h>

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

/* Delete the node at the n-th place in the list.
 * Return the deleted node address.
 * Null is return in case of error.
 */
node_t* delete_node(node_t *node, unsigned int n)
{
    node_t *tmp = node;
    unsigned int cpt = 0;

    if (!tmp)
        return NULL;

    if (n == 0)
        node = node->next;

    while (tmp->next && cpt < n) {
        tmp = tmp->next;
        cpt++;
    }

    if (cpt != n)
        return NULL;

    if (tmp->prev)
        tmp->prev->next = tmp->next;
    if (tmp->next)
        tmp->next->prev = tmp->prev;

    return tmp;
}

node_t* add_node(node_t *node, node_t *new_node, unsigned int n)
{
    node_t *tmp = node;
    unsigned int cpt = 0;

    if (!tmp || !node || !new_node)
        return NULL;

    if (n == 0)
        node = new_node;

    while (tmp->next && cpt < n) {
        tmp = tmp->next;
        cpt++;
    }

    if (cpt != n)
        return node;

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
