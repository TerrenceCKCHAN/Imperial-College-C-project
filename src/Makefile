CC      = gcc
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -Werror -pedantic
TARGETS = assemble  emulate
COMMON_OBJS = assemble.o emulate.o

.SUFFIXES: .c .o

.PHONY: all clean

all: $(TARGETS)

assemble:   assemble.o  $(COMMON_OBJS)
	$(CC) $(CFLAG) -o $@ $^

emulate:    emulate.o   $(COMMON_OBJS)
	$(CC) $(CFLAG) -o $@ $^

clean:
	rm -f $(wildcard *.o)
	rm -f assemble
	rm -f emulate
