CC      = gcc
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -Werror -pedantic

.SUFFIXES: .c .o

.PHONY: all clean

all: assemble emulate

assemble: assembler/assemble.o  assembler/ADT_linkedlist.o assembler/ass_branch.o assembler/ass_dp.o assembler/ass_multiply.o assembler/ass_sdt.o assembler/ass_util.o assembler/firstpass.o assembler/parser.o assembler/secondpass.o assembler/table.o assembler/tokenizer.o

emulate: emulator/emulate.o emulator/emu_branch.o emulator/emu_decode.o emulator/emu_dp.o emulator/emu_io.o emulator/emu_multiply.o emulator/emu_sdt.o emulator/emu_util.o