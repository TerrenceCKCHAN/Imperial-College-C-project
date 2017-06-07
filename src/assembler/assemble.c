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
    char* lines[100];
    LINE_TOKEN* line_tokens[100];
    u32* instruction = malloc(sizeof(instruction));
    u32 numOfLines;
    u32 numOfInstructions;
    numOfLines = sourceFileReader(lines, argv[1]);
//    numOfLines = sourceFileReader(lines, "/homes/klc116/arm11_1617_testsuite/test_cases/add01.s");
/*    printf("%d\n", numOfLines);
    for(int i = 0; i < numOfLines; i++) {
        printf("%s\n",lines[i]);
    }*/
    fileToTokens(line_tokens, lines, numOfLines);
    printTokens(line_tokens, numOfLines);
    struct Linkedlist* symbolTable = getNewlist();
    firstpass(line_tokens, &symbolTable, numOfLines);
//    printLinkedList(symbolTable);
    numOfInstructions = secondpass(line_tokens, instruction, &symbolTable, numOfLines);
    for(int i = 0; i < numOfInstructions; i++) {
        printf("Instruction %d = %x\n", i, instruction[i]);
    }
//    binaryFileWriter(instruction, "/homes/klc116/out.bin");
    binaryFileWriter(instruction, argv[2], numOfInstructions);
    free(symbolTable);
/*
//    fileToTokens(line_tokens, lines, numOfLines);
//    printTokens(line_tokens, numOfLines);
    INSTRUCTION* instr = malloc(sizeof(INSTRUCTION));
    instr->instr.dp = malloc(sizeof (DATAPROCESSING_INSTR));
    LINE_TOKEN* line_token = malloc(sizeof(LINE_TOKEN));
    char line[] = "Add r1, #0xff00";
    lineToTokens(line_token, line);
    strcpy(instr->type,"dataprocessing");
    assembleAdd(line_token, instr);
    printBit1(assembleInstructions(instr));
*/
    return EXIT_SUCCESS;
}


