#ifndef ARM11_06_TOKENIZER_H
#define ARM11_06_TOKENIZER_H

enum TOKEN_TYPE{
    label, operands
};

typedef struct{
    enum TOKEN_TYPE type;
    char label[512];
    char opcode[4];
    char *operands[10];
    int numOfOperands;
}LINE_TOKEN;

void LineToTokens(LINE_TOKEN* line_token, char line[]);
void FiletoTokens(LINE_TOKEN* line_tokens[], char* line[]);
void printToken(LINE_TOKEN* line_token);
void printTokens(LINE_TOKEN* line_token[]);
#endif //ARM11_06_TOKENIZER_H
