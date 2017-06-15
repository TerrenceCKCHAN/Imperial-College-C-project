/////////////////////////////////////////////////////////////////////////////////////////
//C Group Project - First Year (2016-2017)
//File: assembler.c
//Group: 6
//Member: Cheung, Ka (klc116), Mang, Hao (hxm16), Cheuk, Ki (kfc216), Chan, Chun (ckc116)
/////////////////////////////////////////////////////////////////////////////////////////
#include "assemble.h"
#include "ass_io.h"

int main1(int argc, char **argv){
    memoryPos = 0;
    char* lines[MAX_NUMBER_OF_LINES];
    LINE_TOKEN* line_tokens[MAX_NUMBER_OF_LINES];
    u32 instruction[MAX_NUMBER_OF_LINES];
    u32 numOfLines;
    u32 numOfInstructions;

    numOfLines = sourceFileReader(lines, argv[1]);
//    numOfLines = sourceFileReader(lines, "/homes/klc116/CLionProjects/arm11_06/programs/gpio.s");

    fileToTokens(line_tokens, lines, numOfLines);
    printTokens(line_tokens, numOfLines);

    struct Linkedlist* symbolTable = getNewlist();

    numOfInstructions = firstpass(line_tokens, &symbolTable, numOfLines);

    secondpass(line_tokens, instruction, &symbolTable, numOfLines, numOfInstructions);

    u32* allInstructions = malloc(sizeof(instruction) + sizeof(Memory));

    memcpy(allInstructions, instruction, sizeof(instruction));
    memcpy(allInstructions + numOfInstructions, Memory, sizeof(Memory));

    for(int i = 0; i < numOfInstructions + memoryPos; i++) {
        printf("Instruction %d = %x\n", i, allInstructions[i]);
    }
    printLinkedList(symbolTable);

  //  binaryFileWriter(allInstructions, "/homes/klc116/CLionProjects/arm11_06/programs/kernel.img", numOfInstructions + memoryPos);
    binaryFileWriter(allInstructions, argv[2], numOfInstructions + memoryPos);

    free(symbolTable);

/*
    ////////////TRY TO IMPLEMENT BST without destroying linked list////////////////
    struct BST* symbolTable = getNewinitTree((void*)stringcmp);

    numOfInstructions = firstpass(line_tokens, &symbolTable, numOfLines);

    secondpass(line_tokens, instruction, &symbolTable, numOfLines, numOfInstructions);

    u32* allInstructions = malloc(sizeof(instruction) + sizeof(Memory));

    memcpy(allInstructions, instruction, sizeof(instruction));
    memcpy(allInstructions + numOfInstructions, Memory, sizeof(Memory));

    for(int i = 0; i < numOfInstructions + memoryPos; i++) {
        printf("Instruction %d = %x\n", i, allInstructions[i]);
    }

    printBST(symbolTable);

//    binaryFileWriter(allInstructions, "/homes/klc116/CLionProjects/arm11_06/programs/kernel.img", numOfInstructions + memoryPos);
    binaryFileWriter(allInstructions, argv[2], numOfInstructions + memoryPos);

    free(symbolTable);
*/
    return EXIT_SUCCESS;
}


