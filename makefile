CC=cc 
CFLAGS=-Wall -Wextra -pedantic -ggdb 
LIBS=
SRC=src/main.c src/ask.c src/users.c src/questions.c src/helper.c

build:
	$(CC) $(CFLAGS) -o ask $(SRC)
run:
	./ask 
gdb:
	gdb ./ask 
val:
	valgrind ./ask
