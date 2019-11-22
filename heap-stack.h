#ifndef HEAP_STACK_H
#define HEAP_STACK_H

#include <stddef.h>

int heap_stack_push(void);
void heap_stack_pop(int *stack_frame);
void *stack_malloc(size_t len);

#define stack_scope  \
    int _##__LINE__##__FILE__ __attribute__((__unused__,                     \
                             __cleanup__(heap_stack_pop))) = heap_stack_push()

#endif
