#include "tokenizer.h"
#include "assemble.h"

void LineToTokens(LINE_TOKEN* line_token, char line[]) {
    char *token;
    char *rest = line;
    int pos = 0;

    while((token = strtok_r(rest, " ,", &rest))){
        int length = strlen(token);
        if(pos == 0) {
            if(token[length - 1] == ':') {
                line_token->type = label;
                strcpy(line_token->label, token);
            } else {
                line_token->type = operands;
                strcpy(line_token->opcode, token);
            }
        } else {
            line_token->operands[pos - 1] = token;
        }
        pos++;
    }
    line_token->numOfOperands = pos - 1;
}

void printToken(LINE_TOKEN* line_token) {
    switch(line_token->type) {
        case label:
            printf("label: %s\n", line_token->label);
            break;
        case operands:
            printf("Opcode: %s\n", line_token->opcode);
            break;
    }
    for(int index = 0; index < line_token->numOfOperands; index++) {
        printf("Operand %d: %s\n", index, line_token->operands[index]);
    }
}
