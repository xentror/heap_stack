#ifndef HEAP_STACK_HELPERS_H
#define HEAP_STACK_HELPERS_H

#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>

int my_getrandom(void *buf, size_t buflen, unsigned int flags);

#define tid_printf(...)  \
    printf("thread id: %ld -> ", syscall(__NR_gettid));                       \
    printf(__VA_ARGS__);

#endif /* !HEAP_STACK_HELPERS_H */
