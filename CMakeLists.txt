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
        src/emulator/single_data_tran.c src/assembler/assemble.h)



add_executable(arm11_06 ${SOURCE_FILES})