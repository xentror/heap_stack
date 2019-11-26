#include "heap-stack.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define PAGE_SIZE 4096

typedef struct heap_stack_t {
    /* A pointer to the base memory of the heap stack */
    void *mem;

    /* A pointer to the address of the previous stack frame */
    size_t *prev_frame;

    /* A pointer to the end of the stack frame */
    char *end_frame;

    /* The size of the heap stack */
    size_t size;

    /* The number of stack frame in the heap stack */
    int nb_stack_frame;
} heap_stack_t;

heap_stack_t *h_stack_g = NULL;

static heap_stack_t *heap_stack_init(heap_stack_t *heap_stack)
{
    return memset(heap_stack, 0, sizeof(heap_stack_t));
}

static heap_stack_t *heap_stack_new(void)
{
    heap_stack_t *heap_stack = malloc(sizeof(heap_stack_t));
    if (heap_stack == NULL) {
        return NULL;
    }

    return heap_stack_init(heap_stack);
}

static void heap_stack_wipe(heap_stack_t *heap_stack)
{
    free(heap_stack->mem);
    free(heap_stack);
}

static void heap_stack_delete(heap_stack_t **heap_stack)
{
    heap_stack_wipe(*heap_stack);
    *heap_stack = NULL;
}

static size_t heap_stack_len(heap_stack_t *heap_stack)
{
    return heap_stack->end_frame - (char*)heap_stack->mem;
}

static int heap_stack_push_frame(heap_stack_t *heap_stack)
{
    size_t prev_stack_addr;
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
        heap_stack->nb_stack_frame++;
        return 0;
    }
    if (heap_stack_len(heap_stack) >= heap_stack->size) {
        return -1;
    }

    prev_stack_addr = (size_t)heap_stack->prev_frame;
    heap_stack->prev_frame = (size_t*)heap_stack->end_frame;
    *heap_stack->prev_frame = prev_stack_addr;
    heap_stack->end_frame += sizeof(size_t);
    heap_stack->nb_stack_frame++;
    return 0;
}

static int heap_stack_pop_frame(heap_stack_t *heap_stack)
{
    if (heap_stack == NULL || heap_stack->mem == NULL) {
        return -1;
    }

    if (heap_stack->nb_stack_frame == 0) {
        return 0;
    }

    heap_stack->end_frame = (void*)heap_stack->prev_frame;
    if (heap_stack->prev_frame != heap_stack->mem) {
        heap_stack->prev_frame = (size_t*)*heap_stack->prev_frame;
    }
    heap_stack->nb_stack_frame--;
    return 0;
}

int heap_stack_push(void)
{
    if (h_stack_g == NULL) {
        h_stack_g = heap_stack_new();
    }

    printf("\npush stack frame n° %d\n", h_stack_g->nb_stack_frame);
    heap_stack_push_frame(h_stack_g);
    return h_stack_g->nb_stack_frame;
}

void heap_stack_pop(int *stack_frame)
{
    (void)stack_frame;
    heap_stack_pop_frame(h_stack_g);
    printf("pop stack frame n° %d\n\n", h_stack_g->nb_stack_frame);
}

void *stack_malloc(size_t len)
{
    char *res_ptr = NULL;

    if (!h_stack_g || len + heap_stack_len(h_stack_g) >= h_stack_g->size) {
        return NULL;
    }

    res_ptr = h_stack_g->end_frame;
    h_stack_g->end_frame += len;

    return res_ptr;
}

__attribute__((__destructor__))static void h_stack_shutdown(void)
{
    if (h_stack_g == NULL) {
        return;
    }
    assert (h_stack_g->mem == h_stack_g->prev_frame);
    assert (heap_stack_len(h_stack_g) == 0);
    heap_stack_delete(&h_stack_g);
}
