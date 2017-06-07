cmake_minimum_required(VERSION 3.7)
project(arm11_06)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/assembler/assemble.c
        src/emulator/emulate.c
        src/emulator/dataprocessing.c
        src/emulator/emulate.h
        src/emulator/decode.c
        src/emulator/branch.c
        src/emulator/decode.h
        src/emulator/emu_io.c
        src/emulator/emu_util.c
        src/emulator/multiply.c
        src/emulator/single_data_tran.c
        src/assembler/assemble.h
        src/assembler/tokenizer.c
        src/assembler/tokenizer.h
        src/assembler/parser.c
        src/assembler/parser.h
        src/assembler/table.c
        src/assembler/ADT_linkedlist.c
        src/assembler/ass_util.c
        src/assembler/firstpass.c
        src/assembler/firstpass.h
        src/emulator/instruction.h
        src/assembler/secondpass.c
        src/assembler/data_processing.c
        src/assembler/multiply_instructions.c
        src/assembler/branch.c
        )

add_executable(arm11_06 ${SOURCE_FILES})