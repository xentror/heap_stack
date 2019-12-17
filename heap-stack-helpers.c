#include "heap-stack-helpers.h"

int my_getrandom(void *buf, size_t buflen, unsigned int flags)
{
    return (int)syscall(SYS_getrandom, buf, buflen, flags);
}
