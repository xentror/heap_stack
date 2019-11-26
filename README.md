# Heap Stack

This project is about creating a stack on the heap based on the
attributes of GCC, cleanup, constructor, destructor.
This stack is used to automatically wipe memory allocated on the heap.

## Usage:

### Use the library:

You need to link your library to your binary by running somthing like this:

```$ gcc -L<library_location> <CFLAGS> [...] -lheap-stack```

### Example:

```
int main(void)
{
    stack_scope;
    int *array = stack_malloc(10 * sizeof(int));

    /* Any other thing you need to do */
    return 0;
} /* array is freed */
```

## Compilation:

### All:
This compile test bin example and the shared library.

```$ make all```

### Library:
```$ make heap-stack.so```

### Test Bin:
```$ make heap_stack```

### Debug:
```$ make debug <target>```

### Asan:
```$ make asan <target>```
