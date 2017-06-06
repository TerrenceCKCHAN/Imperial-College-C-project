#include "tokenizer.h"
#include "assemble.h"

//Convert the line read in into tokens stored in a structure
//PRE: Pointer to the token structure and the line as a string
//POST: Change the values inside the tokens to what the line specifies
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

//Print the token structure
//PRE: the pointer to the token structure
//POST: Whether the line is a label or an opcode and all it's oprands separated
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
