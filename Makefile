CC=gcc
CFLAGS=-Werror -Wall -Wextra -pedantic
HEAP_STACK_OBJ=heap-stack.o

all: heap_stack

debug: CFLAGS += -g
debug: all

asan: CFLAGS += -fsanitize=address
asan: all

heap_stack: ${STACK_OBJ} ${HEAP_STACK_OBJ}
	${CC} ${CFLAGS} -o heap-stack ${STACK_OBJ} ${HEAP_STACK_OBJ} heap-stack-tests.c

clean:
	rm -rf ${HEAP_STACK_OBJ}
