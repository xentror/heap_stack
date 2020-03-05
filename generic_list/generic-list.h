#ifndef GENERIC_LIST_H
#define GENERIC_LIST_H

#include "linked-list.h"

#define offsetof(type, attr) ((size_t)&(((type*)0)->attr))
#define get_struct_addr(attr_addr, type, attr) ((type*)((char*)attr_addr - offsetof(type, attr)))

#define glist_create(type)  \
    ({                                                                       \
        type *list = malloc(sizeof(type));                                   \
        list->node = create_node();                                          \
                                                                             \
        list;                                                                \
    })

#define glist_get_next_node(type, list)  \
    ({                                                                       \
        type *res_list = NULL;                                               \
        node_t *node = list->node;                                           \
        node = get_next_node(node);                                          \
                                                                             \
        if (node)                                                            \
            res_list = get_struct_addr(node, type, node);                    \
                                                                             \
        res_list;                                                            \
    })

#define glist_get_prev_node(type, list)  \
    ({                                                                       \
        type *res_list = NULL;                                               \
        node_t *node = list->node;                                           \
        node = get_prev_node(node);                                          \
                                                                             \
        if (node)                                                            \
            res_list = get_struct_addr(node, type, node);                    \
                                                                             \
        res_list;                                                            \
    })

#define glist_delete_node(type, list, n)  \
    ({                                                                       \
        type *res_list = NULL;                                               \
        node_t *node = list->node;                                           \
        node = delete_node(node, n);                                         \
                                                                             \
        if (node)                                                            \
            res_list = get_struct_addr(node, type, node)                     \
                                                                             \
        res_list;                                                            \
    })


#define glist_add_node(type, list, n)  \
    ({                                                                       \
        type *res_list = NULL;                                               \
        node_t *node = list->node;                                           \
        node = add_node(node, n);                                            \
                                                                             \
        if (node)                                                            \
            res_list = get_struct_addr(node, type, node);                    \
                                                                             \
        res_list;                                                            \
    })

#define glist_erase(type, list)  \
    ({                                                                       \
        type *_list = list;                                                  \
        unsigned int _cpt = 0;                                               \
                                                                             \
        while (_list) {                                                      \
            node_t *node = _list->node;                                      \
            free(_list);                                                     \
            delete_node(node, cpt);                                          \
                                                                             \
            _cpt++;                                                          \
            if (!node)                                                       \
                break;                                                       \
                                                                             \
            _list = get_struct_addr(node, type, node);                       \
        }                                                                    \
                                                                             \
        _cpt;                                                                \
    })

#endif /* GENERIC_LIST_H */
