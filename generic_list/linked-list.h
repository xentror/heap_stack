#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct node_t node_t;

node_t* create_node();
node_t* get_next_node(node_t *node);
node_t* get_prev_node(node_t *node);
node_t* delete_node(node_t *node, unsigned int n);
node_t* add_node(node_t *node, node_t *new_node, unsigned int n);
unsigned int get_size_list(node_t *node);
#endif /* LINKED_LIST_H */
