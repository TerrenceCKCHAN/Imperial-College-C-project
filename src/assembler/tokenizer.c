/////////////////////////////////////////////////////////////////////////////////////////
//C Group Project - First Year (2016-2017)
//File: tokenizer.c
//Group: 6
//Member: Cheung, Ka (klc116), Mang, Hao (hxm16), Cheuk, Ki (kfc216), Chan, Chun (ckc116)
/////////////////////////////////////////////////////////////////////////////////////////
#include "tokenizer.h"
#include "assemble.h"
/////////////////////////////////////////////////////////////////////////////////////////
//Convert the line read in into tokens stored in a structure
//PRE: Pointer to the token structure and the line as a string
//POST: Change the values inside the tokens to what the line specifies
/////////////////////////////////////////////////////////////////////////////////////////
void lineToTokens(LINE_TOKEN *line_token, char *line) {
    char *token;
    char *rest = line;
    int pos = 0;

    while((token = strtok_r(rest, " ,", &rest))){
        int length = (int) strlen(token);
        if(pos == 0) {
            if(token[length - 1] == ':') {
                line_token->type = label;
                token[length - 1] = '\0';
                strcpy(line_token->str.label, token);
            } else {
                line_token->type = operands;
                strcpy(line_token->str.opcode, token);
            }
        } else {
            line_token->operands[pos - 1] = token;
        }
        pos++;
    }
    line_token->numOfOperands = pos - 1;
}
/////////////////////////////////////////////////////////////////////////////////////////
//Convert the file read in into tokens stored in a structure
//PRE: Pointer to the token structure and the line as an array of strings
//POST: Change the values inside the tokens to what the file specifies
/////////////////////////////////////////////////////////////////////////////////////////
void fileToTokens(LINE_TOKEN **line_tokens, char **line, int numOfLines) {
    for(int index = 0; index < numOfLines; index++) {
        line_tokens[index] = malloc(sizeof(LINE_TOKEN));
        lineToTokens(line_tokens[index], line[index]);
        lsltoMov(line_tokens[index]);
    }
}
/////////////////////////////////////////////////////////////////////////////////////////
//Print the token structure
//PRE: the pointer to the token structure
//POST: Whether the line is a label or an opcode and all it's oprands separated
/////////////////////////////////////////////////////////////////////////////////////////
void printToken(LINE_TOKEN* line_token) {
    switch(line_token->type) {
        case label:
            printf("label: %s\n", line_token->str.label);
            break;
        case operands:
            printf("Opcode: %s\n", line_token->str.opcode);
            break;
    }
    for(int index = 0; index < line_token->numOfOperands; index++) {
        printf("Operand %d: %s\n", index, line_token->operands[index]);
    }
}
/////////////////////////////////////////////////////////////////////////////////////////
//Print the token structure
//PRE: the pointer to the array of tokens
//POST: Whether the line is a label or an opcode and all it's oprands separated
/////////////////////////////////////////////////////////////////////////////////////////
void printTokens(LINE_TOKEN* line_token[], int numOfLines) {
    for(int index = 0; index < numOfLines; index++) {
        printToken(line_token[index]);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////
// Change the line with opcode stirng "lsl" to the one with opcode string "mov"
// since lsl is also a function of mov
/////////////////////////////////////////////////////////////////////////////////////////
void lsltoMov(LINE_TOKEN* line_token) {
    if(line_token->type == operands) {
        if(strcmp(line_token->str.opcode, "lsl") == 0) {
            printf("%s\n", line_token->str.opcode);
            char* reg = malloc(sizeof(line_token->operands[0]));
            char* expr = malloc(sizeof(line_token->operands[1]));
            for(int i = 0; i < line_token->numOfOperands; i++) {
                printf("Operand %d = %s\n", i, line_token->operands[i]);
            }
            strcpy(reg, line_token->operands[0]);
            strcpy(expr, line_token->operands[1]);
            strcpy(line_token->str.opcode, "mov");
            strcpy(line_token->operands[0], reg);
            strcpy(line_token->operands[1], reg);
            line_token->operands[2] = malloc(sizeof("lsl"));
            line_token->operands[3] = malloc(sizeof(line_token->operands[1]));
            strcpy(line_token->operands[2], "lsl");
            strcpy(line_token->operands[3], expr);
            line_token->numOfOperands = 4;
        }
    }
}