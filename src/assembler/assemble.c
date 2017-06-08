#include "assemble.h"
#include "tokenizer.h"
#include "firstpass.h"
#include "../emulator/instruction.h"

void binaryFileWriter(u32 instr[], char *path, u32 numOfInstructions){
    FILE *ofp = fopen(path, "wb");
    if(ofp == NULL){
        fprintf(stderr,"Unable to write file");
        exit(EXIT_FAILURE);
    }

    fwrite(instr, sizeof(u32), numOfInstructions, ofp);
}

void printBit1(u32 x){
    int i;
    u32 mask = (u32) 1 << 31;
    for(i = 0;i < 32;++i){
        printf("%i", (x & mask) != 0);
        x<<=1;
        if(i == 19 | i == 15 | i == 11 | i == 10 |  i == 6 | i == 5 | i == 3 ) {
            printf(" ");
        }
    }

    printf("\n");
}

u32 sourceFileReader(char* lines[], char* filename){
    FILE * pFile;
    char buffer[512];
    u32 index = 0;

    pFile = fopen (filename , "r");
    if (pFile == NULL) {
        perror("Error opening file");
    } else {
        while (fgets(buffer, sizeof(buffer), pFile)) {
            int length = (int)strlen(buffer);
            buffer[length - 1] = '\0';
            lines[index] = malloc(sizeof(buffer));
            strcpy(lines[index], buffer);
            index++;
        }
        fclose (pFile);
    }
    return index;
}

int main(int argc, char **argv){
    memoryPos = 0;
    char* lines[100];
    LINE_TOKEN* line_tokens[100];
    u32 instruction[100];
    u32 numOfLines;
    u32 numOfInstructions;
    numOfLines = sourceFileReader(lines, argv[1]);
//    numOfLines = sourceFileReader(lines, "/homes/ckc116/arm11_1617_testsuite/test_cases/ldr07.s");
/*    printf("%d\n", numOfLines);
    for(int i = 0; i < numOfLines; i++) {
        printf("%s\n",lines[i]);
    }*/
    fileToTokens(line_tokens, lines, numOfLines);
    printTokens(line_tokens, numOfLines);
    struct Linkedlist* symbolTable = getNewlist();
    numOfInstructions = firstpass(line_tokens, &symbolTable, numOfLines);
//    printLinkedList(symbolTable);
    secondpass(line_tokens, instruction, &symbolTable, numOfLines, numOfInstructions);
/*    for(int i = 0; i < numOfInstructions; i++) {
        printf("Instruction %d = %x\n", i, instruction[i]);
    }
    for(int i = 0; i < memoryPos; i++) {
        printf("Instruction %d = %x\n", i + numOfInstructions, Memory[i]);
    }*/
    u32* allInstructions = malloc(sizeof(instruction) + sizeof(Memory));
    memcpy(allInstructions, instruction, sizeof(instruction));
    memcpy(allInstructions + numOfInstructions, Memory, sizeof(Memory));
    for(int i = 0; i < numOfInstructions + memoryPos; i++) {
        printf("Instruction %d = %x\n", i, allInstructions[i]);
    }
    printLinkedList(symbolTable);
//    binaryFileWriter(allInstructions, "/homes/ckc116/out.bin", numOfInstructions);
    binaryFileWriter(allInstructions, argv[2], numOfInstructions + memoryPos);
    free(symbolTable);
/*
//    fileToTokens(line_tokens, lines, numOfLines);
//    printTokens(line_tokens, numOfLines);
    INSTRUCTION* instr = malloc(sizeof(INSTRUCTION));
    instr->instr.dp = malloc(sizeof (DATAPROCESSING_INSTR));
    LINE_TOKEN* line_token = malloc(sizeof(LINE_TOKEN));
    char line[] = "tst r1, r2";
    lineToTokens(line_token, line);
    strcpy(instr->type,"dataprocessing");
    assembleTst(line_token, instr);
    printBit1(assembleInstructions(instr));


*/

    char* opcode;
    struct Linkedlist *table;
    return EXIT_SUCCESS;
}


