//
// Created by klc116 on 6/7/17.
//

#include "assemble.h"
#include "tokenizer.h"
#include "../emulator/decode.h"

u32 secondpass(LINE_TOKEN* line_tokens[], u32* instructions,struct Linkedlist **symbolTable, int numOfLines) {
    u32 memoryIndex = 0;
    for(int pos = 0; pos < numOfLines; pos++) {
        INSTRUCTION* instr = malloc(sizeof(INSTRUCTION));
        if(line_tokens[pos]->type == operands) {
            void (*assemble)(LINE_TOKEN*, INSTRUCTION*);
//            printf("%s\n", line_tokens[pos]->str.opcode);
            assemble = lookUpfunction(line_tokens[pos]->str.opcode);
//            printf("hi2\n");
//            if(assemble == &assembleMov) {
//                printf("Got it\n");
//            }
            assemble(line_tokens[pos], instr);
//            printf("Type = %s\n", instr->type);
//            printDecodedInstruction(instr);
//            printf("hi4\n");
            instructions[memoryIndex] = assembleInstructions(instr);
//            printf("%x\n", assembleInstructions(instr));
            memoryIndex++;
        }
    }
    return memoryIndex;
}