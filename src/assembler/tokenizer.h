#ifndef ARM11_06_TOKENIZER_H
#define ARM11_06_TOKENIZER_H

enum TOKEN_TYPE{
    label, operands
};

typedef struct{
    enum TOKEN_TYPE type;
    union{
        char label[512];
        char opcode[4];
    }str;
    char *operands[10];
    int numOfOperands;
}LINE_TOKEN;

void lineToTokens(LINE_TOKEN *line_token, char line[]);
void fileToTokens(LINE_TOKEN **line_tokens, char **line, int numOfLines);
void printToken(LINE_TOKEN* line_token);
void printTokens(LINE_TOKEN* line_token[], int numOfLines);
#endif //ARM11_06_TOKENIZER_H
