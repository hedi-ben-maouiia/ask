CFLAGS=-Wall -Wextra -std=c11 -pedantic -ggdb 
CC=gcc 
CLIBS=vector.c

askfm:
	$(CC) $(CFLAGS) main.c -o askfm  $(CLIBS)
clean: 
	rm -rf askfm 
