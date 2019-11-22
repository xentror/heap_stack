#include "heap-stack.h"

#include <stdlib.h>
#include <string.h>

#define PAGE_SIZE 4096

typedef struct heap_stack_t {
    /* A pointer to the base memory of the heap stack */
    void *mem;

    /* A pointer to the address of the previous stack frame */
    size_t *prev_frame;

    /* A pointer to the end of the stack frame */
    char *end_frame;

    /* The len of the heap stack */
    size_t len;

    /* The size of the heap stack */
    size_t size;

    /* The number of stack frame in the heap stack */
    int nb_stack_frame;
} heap_stack_t;

heap_stack_t *h_stack_g = NULL;

heap_stack_t *heap_stack_init(heap_stack_t *heap_stack)
{
    return memset(heap_stack, 0, sizeof(heap_stack_t));
}

heap_stack_t *heap_stack_new(void)
{
    heap_stack_t *heap_stack = malloc(sizeof(heap_stack_t));
    if (heap_stack == NULL) {
        return NULL;
    }

    return heap_stack_init(heap_stack);
}

void heap_stack_wipe(heap_stack_t *heap_stack)
{
    free(heap_stack->mem);
    free(heap_stack);
}

void heap_stack_delete(heap_stack_t **heap_stack)
{
    heap_stack_wipe(*heap_stack);
    *heap_stack = NULL;
}

int heap_stack_push_frame(heap_stack_t *heap_stack)
{
    if (heap_stack == NULL) {
        return -1;
    }

    if (heap_stack->mem == NULL) {
        heap_stack->mem = malloc(100 * PAGE_SIZE);
        if (heap_stack->mem == NULL) {
            exit(-1);
        }
        heap_stack->prev_frame = heap_stack->mem;
        heap_stack->end_frame = heap_stack->mem;
        heap_stack->size = 100 * PAGE_SIZE;
    }
    if (heap_stack->len >= heap_stack->size) {
        return -1;
    }

    *heap_stack->prev_frame = (size_t)heap_stack->mem;
    heap_stack->end_frame += sizeof(size_t);
    heap_stack->len += sizeof(size_t);
    heap_stack->nb_stack_frame++;
    return 0;
}

int heap_stack_pop_frame(heap_stack_t *heap_stack)
{
    if (heap_stack == NULL || heap_stack->mem == NULL) {
        return -1;
    }

    if (heap_stack->nb_stack_frame == 0) {
        return 0;
    }

    heap_stack->len = heap_stack->end_frame - (char*)heap_stack->prev_frame;
    heap_stack->end_frame = (void*)heap_stack->prev_frame;
    heap_stack->prev_frame = (size_t*)*heap_stack->prev_frame;
    heap_stack->nb_stack_frame--;
    return 0;
}

int heap_stack_push(void)
{
    if (h_stack_g == NULL) {
        h_stack_g = heap_stack_new();
    }

    heap_stack_push_frame(h_stack_g);
    return h_stack_g->nb_stack_frame;
}

void heap_stack_pop(int *stack_frame)
{
    (void)stack_frame;
    heap_stack_pop_frame(h_stack_g);
}

void *stack_malloc(size_t len)
{
    char *res_ptr = NULL;

    if (!h_stack_g || len + h_stack_g->len >= h_stack_g->size) {
        return NULL;
    }

    res_ptr = h_stack_g->end_frame;
    h_stack_g->len += len;
    h_stack_g->end_frame += len;

    return res_ptr;
}
