#include "heap-stack.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <time.h>

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

    /* A random value to ensure that stack frames are not corrupted */
    int canary;
} heap_stack_t;

/* TODO: make it thread dependant and safe */
static heap_stack_t *h_stack_g = NULL;

static heap_stack_t *heap_stack_init(heap_stack_t *heap_stack)
{
    time_t t;

    memset(heap_stack, 0, sizeof(heap_stack_t));

    /* TODO: use /dev/urandom to ensure more safety */
    srand((unsigned) time(&t));
    heap_stack->canary = rand();

    return heap_stack;
}

static heap_stack_t *heap_stack_new(void)
{
    heap_stack_t *heap_stack = malloc(sizeof(heap_stack_t));
    if (heap_stack == NULL) {
        fprintf(stderr, "unable to allocate the heap stack.\n");
        exit(1);
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


static void heap_stack_allocate_new_memory(heap_stack_t *heap_stack)
{
    heap_stack->mem = malloc(100 * PAGE_SIZE);
    if (heap_stack->mem == NULL) {
        fprintf(stderr, "unable to allocate memory for the heap stack.\n");
        exit(1);
    }

    heap_stack->prev_frame = heap_stack->mem;
    heap_stack->end_frame = heap_stack->mem;
    heap_stack->size = 100 * PAGE_SIZE;
    heap_stack->nb_stack_frame++;
}

static int heap_stack_push_frame(heap_stack_t *heap_stack)
{
    size_t prev_stack_addr;
    int *canary_ptr;

    if (heap_stack->mem == NULL) {
        heap_stack_allocate_new_memory(heap_stack);
    }

    /* check that we have enough space for the 2 canaries (sizeof(init)) and
     * the previous stack frame address save (sizeof(size_t)).
     */
    if (heap_stack_len(heap_stack) + sizeof(int) * 2 + sizeof(size_t)
    >=  heap_stack->size)
    {
        fprintf(stderr, "no space left in the heap stack.");
        return -1;
    }

    prev_stack_addr = (size_t)heap_stack->prev_frame;
    canary_ptr = (int*)heap_stack->end_frame;

    /* Put the first canary */
    *canary_ptr = heap_stack->canary;
    heap_stack->end_frame += sizeof(int);

    /* Save the previous stack frame address */
    heap_stack->prev_frame = (size_t*)heap_stack->end_frame;
    *heap_stack->prev_frame = prev_stack_addr;
    heap_stack->end_frame += sizeof(size_t);

    /* Put the last canary */
    canary_ptr = (int*)heap_stack->end_frame;
    *canary_ptr = heap_stack->canary;
    heap_stack->end_frame += sizeof(int);

    heap_stack->nb_stack_frame++;
    return 0;
}

static int heap_stack_check_canaries(heap_stack_t *heap_stack)
{
    int canary;
    const char *prev_frame = (char*)heap_stack->prev_frame;

    canary = *(int*)(prev_frame + sizeof(size_t));
    if (canary != heap_stack->canary) {
        goto error;
    }
    canary = *(int*)(prev_frame - sizeof(int));
    if (canary != heap_stack->canary) {
        goto error;
    }

    return 0;

  error:
    fprintf(stderr, "heap stack canary corrupted.\n");
    return -1;
}

static int heap_stack_pop_frame(heap_stack_t *heap_stack)
{

    if (!heap_stack || !heap_stack->mem || !heap_stack->nb_stack_frame) {
        fprintf(stderr, "try to pop an empty heap stack.\n");
        return -1;
    }

    heap_stack->end_frame = (void*)heap_stack->prev_frame;

    if (heap_stack->nb_stack_frame > 1) {
        assert (heap_stack->mem != heap_stack->prev_frame);

        if (heap_stack_check_canaries(heap_stack) < 0) {
            return -1;
        }

        /* Put the end frame on the first canary */
        heap_stack->end_frame -= sizeof(int);

        /* Restore the previous stack frame ptr */
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

    if (heap_stack_push_frame(h_stack_g) < 0) {
        exit(1);
    }

#ifndef NDEBUG
    printf("\npush stack frame n° %d\n", h_stack_g->nb_stack_frame);
#endif

    return h_stack_g->nb_stack_frame;
}

void heap_stack_pop(int *stack_frame)
{
    assert (*stack_frame == h_stack_g->nb_stack_frame);

    if (heap_stack_pop_frame(h_stack_g) < 0) {
        exit(1);
    }

#ifndef NDEBUG
    printf("pop stack frame n° %d\n\n", h_stack_g->nb_stack_frame);
#endif
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

__attribute__((__destructor__)) static void h_stack_shutdown(void)
{
    if (h_stack_g == NULL) {
        return;
    }

    heap_stack_delete(&h_stack_g);
}
