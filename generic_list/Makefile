CC= gcc
CFLAGS= -Wall -Werror -Wextra -g
LIST_OBJ= linked-list.o
TEST_OBJ= glist-test.o

all: list.so list-test libglist.a

debug: CFLAGS+= -g -fsanitize=address
debug: list-test

list.so: ${LIST_OBJ}
	${CC} ${CFLAGS} -o list.so ${LIST_OBJ} -shared

list-test: ${LIST_OBJ} ${TEST_OBJ}
	${CC} ${CFLAGS} -o list-test ${LIST_OBJ} ${TEST_OBJ}

libglist.a: ${LIST_OBJ}
	ar rcs libglist.a ${LIST_OBJ}

clean:
	rm -rf ${LIST_OBJ} ${TEST_OBJ} list.so list-test libglist.a
