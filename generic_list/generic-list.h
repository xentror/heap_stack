#ifndef GENERIC_LIST_H
#define GENERIC_LIST_H

#include "linked-list.h"

#include <stddef.h>
#include <stdlib.h>

#define get_struct_addr(attr_addr, type, attr) ((type*)((char*)attr_addr - offsetof(type, attr)))

#define glist_create(type)  \
    ({                                                                       \
        type *_list = calloc(sizeof(type), 0);                               \
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
            _res_list = get_struct_addr(_node, type, node);                  \
                                                                             \
        _res_list;                                                           \
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


#define glist_get_size(type, list)  \
    ({                                                                       \
        type *_list = list;                                                  \
        unsigned int size = 0;                                               \
                                                                             \
        if (_list)                                                           \
            size = get_size_list(&(_list->node));                            \
                                                                             \
        size;                                                                \
    })

#define glist_delete_node(type, list, n)  \
    ({                                                                       \
        type *_list = list;                                                  \
        node_t *_node = &_list->node;                                        \
                                                                             \
        _node = delete_node(_node, n);                                       \
                                                                             \
        if (_node && n == 0) {                                               \
            node_t *_next_node = get_next_node(_node);                       \
                                                                             \
            if (_next_node)                                                  \
                _list = get_struct_addr(_next_node, type, node);             \
            else                                                             \
                _list = NULL;                                                \
        }                                                                    \
        if (_node)                                                           \
            free(get_struct_addr(_node, type, node));                        \
                                                                             \
        _list;                                                               \
    })

#define glist_add_node(type, list, new_list, n)  \
    ({                                                                       \
        node_t *_node;                                                       \
        type *_list = list;                                                  \
        type *_new_list = new_list;                                          \
                                                                             \
        if (!_list || !new_list)                                             \
            _list = _new_list;                                               \
        else {                                                               \
            _node = add_node(&(_list->node), &(_new_list->node), n);         \
            _list = get_struct_addr(_node, type, node);                      \
        }                                                                    \
                                                                             \
        _list;                                                               \
    })

#define glist_erase(type, list)  \
    ({                                                                       \
        type **_list = list;                                                 \
        unsigned int _cpt = 0;                                               \
        node_t *_node = &((*_list)->node);                                   \
                                                                             \
        while (_node) {                                                      \
            type *_tmp_list = get_struct_addr(_node, type, node);            \
            _node = get_next_node(_node);                                    \
                                                                             \
            free(_tmp_list);                                                 \
            _cpt++;                                                          \
        }                                                                    \
        *_list = NULL;                                                       \
                                                                             \
        _cpt;                                                                \
    })

#endif /* GENERIC_LIST_H */
