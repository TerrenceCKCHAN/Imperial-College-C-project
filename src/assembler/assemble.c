/////////////////////////////////////////////////////////////////////////////////////////
//C Group Project - First Year (2016-2017)
//File: assembler.c
//Group: 6
//Member: Cheung, Ka (klc116), Mang, Hao (hxm16), Cheuk, Ki (kfc216), Chan, Chun (ckc116)
/////////////////////////////////////////////////////////////////////////////////////////
#include "assemble.h"

int main(int argc, char **argv){
    memoryPos = 0;
    char *lines[MAX_NUMBER_OF_LINES];
    LINE_TOKEN *line_tokens[MAX_NUMBER_OF_LINES];
    u32 instruction[MAX_NUMBER_OF_LINES];
    u32 numOfLines;
    u32 numOfInstructions;
    //Read the source file from the provided path
    numOfLines = sourceFileReader(lines, argv[1]);

    //Change the lines into tokens for processing
    fileToTokens(line_tokens, lines, numOfLines);

    //Initialize symbol table
    struct Linkedlist* symbolTable = getNewlist();

    //first pass: add entries to the symbol table
    numOfInstructions = firstpass(line_tokens, &symbolTable, numOfLines);

    //second pass: assemble instructions
    secondpass(line_tokens, instruction, &symbolTable, numOfLines, numOfInstructions);

    //allocate memory for all instructions
    u32* allInstructions = malloc(sizeof(instruction) + sizeof(Memory));

    //concatenate the instruction array with the memory array
    memcpy(allInstructions, instruction, sizeof(instruction));
    memcpy(allInstructions + numOfInstructions, Memory, sizeof(Memory));

    //write the instructions to the binary file
    binaryFileWriter(allInstructions, argv[2], numOfInstructions + memoryPos);

    return EXIT_SUCCESS;
}


