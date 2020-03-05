CC= gcc
CFALGS= -pedantic -Wall -Werror -Wextra
OBJ= linked-list.o

all: list.so

list.so: ${OBJ}
	${CC} ${CFALGS} -o list.so ${OBJ} -shared

clean:
	rm -rf ${OBJ}
