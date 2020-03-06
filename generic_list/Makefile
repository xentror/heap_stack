CC= gcc
CFLAGS= -Wall -Werror -Wextra -g
LIST_OBJ= linked-list.o
TEST_OBJ= glist-test.o

all: list.so list-test

debug: CFLAGS+= -g -fsanitize=address
debug: list-test

list.so: ${LIST_OBJ}
	${CC} ${CFLAGS} -o list.so ${LIST_OBJ} -shared

list-test: ${OBJ} ${TEST_OBJ}
	${CC} ${CFLAGS} -o list-test ${LIST_OBJ} ${TEST_OBJ}

clean:
	rm -rf ${OBJ} ${TEST_OBJ} list.so list-test
