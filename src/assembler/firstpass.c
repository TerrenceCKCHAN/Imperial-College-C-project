#include "assemble.h"
#include "tokenizer.h"

void firstpass(LINE_TOKEN* line_tokens[], struct Linkedlist* symbolTable, int numOfLines) {
    u32 index = 0;
//    printTokens(line_tokens, numOfLines);
//    printf("numOfLines = %d\n", numOfLines);
    for(int pos = 0; pos < numOfLines; pos++) {
//        printToken(line_tokens[pos]);
//        printf("%d\n", line_tokens[pos]->type);
        if(line_tokens[pos]->type == label) {
//            printf("%s\n", line_tokens[pos]->str.label);
            u32 address = index * 4;
//            printf("hi\n");
            symbolTable = insertElementInNode(symbolTable, line_tokens[pos]->str.label,(u32) address);
            //printLinkedList(symbolTable);
        } else {
            index++;
        }
    }
}