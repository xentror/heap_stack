#ifndef GENERIC_LIST_H
#define GENERIC_LIST_H

#include "linked-list.h"

#include <stddef.h>
#include <stdlib.h>

#define get_struct_addr(attr_addr, type, attr) ((type*)((char*)attr_addr - offsetof(type, attr)))

#define GLIST_INIT(type)  \
glist_create_function(type)                                                  \
                                                                             \
glist_erase_function(type)                                                   \
                                                                             \
glist_get_next_node_function(type)                                           \
                                                                             \
glist_get_prev_node_function(type)                                           \
                                                                             \
glist_get_size_function(type)                                                \
                                                                             \
glist_print_function(type)                                                   \
                                                                             \
glist_delete_at_function(type)                                               \
                                                                             \
glist_insert_at_function(type)                                               \
                                                                             \
glist_pop_function(type)                                                     \
                                                                             \
glist_push_function(type)

#define glist_create_function(type)  \
type##_t* type##_create(void)                                                \
{                                                                            \
    type##_t *list = calloc(sizeof(type##_t), 0);                            \
                                                                             \
    return list;                                                             \
}

#define glist_get_next_node_function(type)  \
type##_t* type##_get_next(type##_t *list)                                    \
{                                                                            \
    node_t *node = NULL;                                                     \
    type##_t *res_list = NULL;                                               \
                                                                             \
    if (!list)                                                               \
        return NULL;                                                         \
                                                                             \
    node = get_next_node(&(list->node));                                     \
    if (node)                                                                \
        res_list = get_struct_addr(node, type##_t, node);                    \
                                                                             \
    return res_list;                                                         \
}

#define glist_get_prev_node_function(type)  \
type##_t* type##get_prev(type##_t *list)                                     \
{                                                                            \
    node_t *node = NULL;                                                     \
    type##_t *res_list = NULL;                                               \
                                                                             \
    if (!list)                                                               \
        return NULL;                                                         \
                                                                             \
    node = get_prev_node(&(list->node));                                     \
    if (node)                                                                \
        res_list = get_struct_addr(node, type##_t, node);                    \
                                                                             \
    return res_list;                                                         \
}

#define glist_get_size_function(type)  \
unsigned int type##_get_size(type##_t *list)                                 \
{                                                                            \
    unsigned int size = 0;                                                   \
                                                                             \
    if (list)                                                                \
        size = get_size_list(&(list->node));                                 \
                                                                             \
    return size;                                                             \
}

#define glist_delete_at_function(type)  \
type##_t* type##_delete_at(type##_t *list, unsigned int n)                   \
{                                                                            \
    node_t *_node = NULL;                                                    \
                                                                             \
    if (!list)                                                               \
        return NULL;                                                         \
                                                                             \
    _node = delete_node(&(list->node), n);                                   \
    if (_node && n == 0) {                                                   \
        node_t *_next_node = get_next_node(_node);                           \
                                                                             \
        if (_next_node)                                                      \
            list = get_struct_addr(_next_node, type##_t, node);              \
        else                                                                 \
            list = NULL;                                                     \
    }                                                                        \
    if (_node)                                                               \
        free(get_struct_addr(_node, type##_t, node));                        \
                                                                             \
    return list;                                                             \
}

#define glist_insert_at_function(type)  \
type##_t* type##_insert_at(type##_t *list, type##_t *new_list,               \
                           unsigned int n)                                   \
{                                                                            \
    node_t *_node;                                                           \
                                                                             \
    if (!list)                                                               \
        list = new_list;                                                     \
    else if (new_list) {                                                     \
        _node = add_node(&(list->node), &(new_list->node), n);               \
        list = get_struct_addr(_node, type##_t, node);                       \
    }                                                                        \
                                                                             \
    return list;                                                             \
}

#define glist_erase_function(type)  \
unsigned int type##_erase(type##_t **list)                                   \
{                                                                            \
    unsigned int cpt = 0;                                                    \
    node_t *_node = NULL;                                                    \
                                                                             \
    if (!list || !(*list))                                                   \
        return cpt;                                                          \
                                                                             \
    _node = &(*list)->node;                                                  \
    while (_node) {                                                          \
        type##_t *tmp_list = get_struct_addr(_node, type##_t, node);         \
        _node = get_next_node(_node);                                        \
                                                                             \
        free(tmp_list);                                                      \
        cpt++;                                                               \
    }                                                                        \
    *list = NULL;                                                            \
                                                                             \
    return cpt;                                                              \
}

#define glist_print_function(type)  \
typedef void (*type##_print_f)(type##_t *list);                              \
                                                                             \
unsigned int type##_print(type##_t *list, type##_print_f print)              \
{                                                                            \
        unsigned int cpt = 0;                                                \
                                                                             \
        printf("list: ");                                                    \
                                                                             \
        while (list) {                                                       \
            node_t *_node = get_next_node(&list->node);                      \
            print(list);                                                     \
            printf(" ");                                                     \
                                                                             \
            cpt++;                                                           \
            if (!_node)                                                      \
                break;                                                       \
                                                                             \
            list = get_struct_addr(_node, type##_t, node);                   \
        }                                                                    \
                                                                             \
        printf("\n");                                                        \
        return cpt;                                                          \
}

#define glist_push_function(type)  \
type##_t* type##_push(type##_t *list, type##_t *new_list)                    \
{                                                                            \
    unsigned int size = 0;                                                   \
                                                                             \
    if (list) {                                                              \
        size = get_size_list(&(list->node));                                 \
    }                                                                        \
    list = type##_insert_at(list, new_list, size);                           \
                                                                             \
    return list;                                                             \
}

#define glist_pop_function(type)  \
type##_t* type##_pop(type##_t *list)                                         \
{                                                                            \
    node_t *_node;                                                           \
    unsigned int size;                                                       \
                                                                             \
    if (list) {                                                              \
        _node = &(list->node);                                               \
        size = get_size_list(_node);                                         \
                                                                             \
        list = type##_delete_at(list, size - 1);                             \
    }                                                                        \
                                                                             \
    return list;                                                             \
}

#endif /* GENERIC_LIST_H */
