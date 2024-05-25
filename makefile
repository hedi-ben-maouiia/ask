CFLAGS=-Wall -Wextra  -pedantic -ggdb 
CC=gcc 
CLIBS=vector.c ask.c

askfm:
	$(CC) $(CFLAGS)  main.c -o askfm  $(CLIBS)
clean: 
	rm -rf askfm 
