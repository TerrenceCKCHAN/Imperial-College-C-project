#include "assemble.h"
#include "tokenizer.h"

u32 firstpass(LINE_TOKEN **line_tokens, struct Linkedlist **symbolTable, int numOfLines) {
    u32 index = 0;
    for(int pos = 0; pos < numOfLines; pos++) {
//        printToken(line_tokens[pos]);
//        printf("%d\n", line_tokens[pos]->type);
        if(line_tokens[pos]->type == label) {
//            printf("%s\n", line_tokens[pos]->str.label);
            u32 address = index * 4;
//            printf("%s %d\n", line_tokens[pos]->str.label, address);
            insertElement(symbolTable, line_tokens[pos]->str.label, (u32*)address);
        } else {
            index++;
        }
    }
    return index;
}

/*
u32 firstpass(LINE_TOKEN **line_tokens, struct BST **symbolTable, int numOfLines) {
    u32 index = 0;
    for(int pos = 0; pos < numOfLines; pos++) {
//        printToken(line_tokens[pos]);
//        printf("%d\n", line_tokens[pos]->type);
        if(line_tokens[pos]->type == label) {
//            printf("%s\n", line_tokens[pos]->str.label);
            u32 address = index * 4;
//            printf("%s %d\n", line_tokens[pos]->str.label, address);
            insertElem(*symbolTable,line_tokens[pos]->str.label,(u32*) address,(void*) strcmp);
        } else {
            index++;
        }
    }
    return index;
}
*/