#ifndef GENERIC_LIST_H
#define GENERIC_LIST_H

#include "linked-list.h"

#define offsetof(type, attr) ((size_t)&(((type*)0)->attr))
#define get_struct_addr(attr_addr, type, attr) ((type*)((char*)attr_addr - offsetof(type, attr)))

#define glist_create(type)  \
    ({                                                                       \
        type *_list = malloc(sizeof(type));                                  \
                                                                             \
        _list;                                                               \
    })

#define glist_get_next_node(type, list)  \
    ({                                                                       \
        type *_res_list = NULL;                                              \
        node_t *_node = &list->node;                                         \
        _node = get_next_node(_node);                                        \
                                                                             \
        if (_node)                                                           \
            res_list = get_struct_addr(_node, type, node);                   \
                                                                             \
        res_list;                                                            \
    })

#define glist_get_prev_node(type, list)  \
    ({                                                                       \
        type *_res_list = NULL;                                              \
        node_t *_node = &list->node;                                         \
        _node = get_prev_node(_node);                                        \
                                                                             \
        if (_node)                                                           \
            res_list = get_struct_addr(_node, type, node);                   \
                                                                             \
        res_list;                                                            \
    })

#define glist_delete_node(type, list, n)  \
    ({                                                                       \
        type *res_list = NULL;                                               \
        node_t *_node = &list->node;                                         \
                                                                             \
        _node = delete_node(node, n);                                        \
        free(list);                                                          \
                                                                             \
        if (_node)                                                           \
            res_list = get_struct_addr(_node, type, node)                    \
                                                                             \
        res_list;                                                            \
    })


#define glist_add_node(type, list, n)  \
    ({                                                                       \
        type *_list = list;                                                  \
        node_t *node = &_list->node;                                         \
        type *_tmp_list = malloc(sizeof(type));                              \
        node_t *_new_node = &_tmp_list->node;                                \
                                                                             \
        _node = add_node(_node, _new_node, n);                               \
        _list = get_struct_addr(_node, type, node)                           \
                                                                             \
        _list;                                                               \
    })

#define glist_erase(type, list)  \
    ({                                                                       \
        type *_list = list;                                                  \
        unsigned int _cpt = 0;                                               \
                                                                             \
        while (_list) {                                                      \
            node_t *_node = &_list->node;                                    \
            free(_list);                                                     \
            delete_node(_node, cpt);                                         \
                                                                             \
            _cpt++;                                                          \
            if (!_node)                                                      \
                break;                                                       \
                                                                             \
            _list = get_struct_addr(_node, type, node);                      \
        }                                                                    \
                                                                             \
        _cpt;                                                                \
    })

#endif /* GENERIC_LIST_H */
