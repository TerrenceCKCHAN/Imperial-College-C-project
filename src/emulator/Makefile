CC      = gcc
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -Werror -pedantic
TARGETS = emulate
COMMON_OBJS = emulate.o emu_branch.o emu_decode.o emu_dp.o emu_io.o emu_multiply.o emu_sdt.o emu_util.o

.SUFFIXES: .c .o

.PHONY: all clean

all: $(TARGETS)

emulate:    emulate.o   $(COMMON_OBJS)
	$(CC) $(CFLAG) -o $@ $^

clean:
	rm -f $(wildcard *.o)
	rm -f assemble
	rm -f emulate


