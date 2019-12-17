CC=gcc
CFLAGS=-Werror -Wall -Wextra -pedantic -fPIC
HEAP_STACK_OBJ= heap-stack.o heap-stack-helpers.o
HEAP_STACK_TESTS_OBJ= heap-stack-tests.o heap-stack-test-1.o heap-stack-test-2.o

all: heap_stack heap-stack.so

debug: CFLAGS += -g
debug: all

asan: CFLAGS += -fsanitize=address
asan: all

heap_stack: ${HEAP_STACK_OBJ} ${HEAP_STACK_TESTS_OBJ}
	${CC} ${CFLAGS} -o heap-stack ${STACK_OBJ} ${HEAP_STACK_OBJ} ${HEAP_STACK_TESTS_OBJ} -lpthread

heap-stack.so: ${HEAP_STACK_OBJ}
	${CC} ${CFLAGS} -o libheap-stack.so ${HEAP_STACK_OBJ} -shared

clean:
	rm -rf ${HEAP_STACK_OBJ} ${HEAP_STACK_TESTS_OBJ}
