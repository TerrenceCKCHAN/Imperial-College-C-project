CC      = gcc
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -Werror -pedantic
TARGETS = assemble
COMMON_OBJS = assemble.o ADT_linkedlist.o ass_branch.o ass_dp.o ass_io.o ass_multiply.o ass_sdt.o ass_util.o firstpass.o parser.o secondpass.o table.o tokenizer.o

.SUFFIXES: .c .o

.PHONY: all clean

all: $(TARGETS)

assemble:   assemble.o  $(COMMON_OBJS)
	$(CC) $(CFLAG) -o $@ $^

clean:
	rm -f $(wildcard *.o)
	rm -f assemble

