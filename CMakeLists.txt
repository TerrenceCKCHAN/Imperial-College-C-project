cmake_minimum_required(VERSION 3.7)
project(arm11_06)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/assembler/assemble.c
        src/emulator/emulate.c
        src/emulator/emu_dp.c
        src/emulator/emulate.h
        src/emulator/emu_decode.c
        src/emulator/emu_branch.c
        src/emulator/emu_decode.h
        src/emulator/emu_io.c
        src/emulator/emu_util.c
        src/emulator/emu_multiply.c
        src/emulator/emu_sdt.c
        src/assembler/assemble.h
        src/assembler/tokenizer.c
        src/assembler/tokenizer.h
        src/assembler/parser.c
        src/assembler/table.c
        src/assembler/ADT_linkedlist.c
        src/assembler/ass_util.c
        src/assembler/firstpass.c
        src/emulator/instruction.h
        src/assembler/secondpass.c
        src/assembler/ass_dp.c
        src/assembler/ass_multiply.c
        src/assembler/ass_branch.c
        src/assembler/ass_sdt.c
        src/assembler/ADT_BST.c programs/game.c)

add_executable(arm11_06 ${SOURCE_FILES})