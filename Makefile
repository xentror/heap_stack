CC=gcc
CFLAGS=-Werror -Wall -Wextra -pedantic -fPIC
LDFLAGS= -L./generic_list -lglist
HEAP_STACK_OBJ= heap-stack.o heap-stack-helpers.o
HEAP_STACK_TESTS_OBJ= test/heap-stack-tests.o test/heap-stack-test-1.o test/heap-stack-test-2.o

all: glist heap-stack heap-stack.so

glist:
	(cd generic_list; make -B)

debug: CFLAGS += -g
debug: all

asan: CFLAGS += -fsanitize=address
asan: all

heap-stack: LDFLAGS+= -lpthread
heap-stack: ${HEAP_STACK_OBJ} ${HEAP_STACK_TESTS_OBJ}
	${CC} ${CFLAGS} ${LDFLAGS} -o heap-stack ${STACK_OBJ} ${HEAP_STACK_OBJ} ${HEAP_STACK_TESTS_OBJ}

heap-stack.so: CFLAGS+= -shared
heap-stack.so: ${HEAP_STACK_OBJ}
	${CC} ${CFLAGS} ${LDFLAGS} -o libheap-stack.so ${HEAP_STACK_OBJ}

clean:
	rm -rf ${HEAP_STACK_OBJ} ${HEAP_STACK_TESTS_OBJ} libheap-stack.so heap-stack
	(cd generic_list; make clean)
