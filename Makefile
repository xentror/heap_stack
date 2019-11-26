CC=gcc
CFLAGS=-Werror -Wall -Wextra -pedantic -fPIC
HEAP_STACK_OBJ=heap-stack.o

all: heap_stack heap-stack.so

debug: CFLAGS += -g
debug: all

asan: CFLAGS += -fsanitize=address
asan: all


heap_stack: ${HEAP_STACK_OBJ}
	${CC} ${CFLAGS} -o heap-stack ${STACK_OBJ} ${HEAP_STACK_OBJ} heap-stack-tests.c

heap-stack.so: ${HEAP_STACK_OBJ}
	${CC} ${CFLAGS} -o libheap-stack.so ${HEAP_STACK_OBJ} -shared -Wl,-soname,libheap-stack.so.1.0

clean:
	rm -rf ${HEAP_STACK_OBJ}
