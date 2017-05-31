cmake_minimum_required(VERSION 3.7)
project(arm11_06)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/assemble.c
        src/emulate.c
        src/dataprocessing.c
        src/emulate.h
        src/decode.c
        src/decode.h
        )


add_executable(arm11_06 ${SOURCE_FILES})