/////////////////////////////////////////////////////////////////////////////////////////
//C Group Project - First Year (2016-2017)
//File: ass_sdt.c
//Group: 6
//Member: Cheung, Ka (klc116), Mang, Hao (hxm16), Cheuk, Ki (kfc216), Chan, Chun (ckc116)
/////////////////////////////////////////////////////////////////////////////////////////
#include "assemble.h"
#include "tokenizer.h"
#include "parser.h"
#include "../emulator/instruction.h"

//void parseExpressioninrect(EXP_IN_RECT* preIndexingExpr, LINE_TOKEN* line_token){
//    int i = 1;
//    int expinrect = 0;
//    int expnotinrect = 0;
//    while(line_token->operands[i] != NULL){
//        if (line_token->operands[i][0]=='[' ){
//            line_token->operands[i] ++;
//            preIndexingExpr->preIndexingExpr[expinrect] = line_token->operands[i];
//            expinrect++;
//        }else if(line_token->operands[i][strlen(line_token->operands[i])-1]==']'){
//            preIndexingExpr->preIndexingExpr[expinrect] = line_token->operands[i];
//            expinrect++;
//        }
//        else {
//            preIndexingExpr->preIndexingExpr[expnotinrect] = line_token->operands[expnotinrect];
//            expnotinrect++;
//        }
//        i++;
//    }
//    preIndexingExpr->numOfPreIndexingExpr=expinrect;
//    preIndexingExpr->numOfPostIndexingExpr=expnotinrect;
//}

void parseExpressioninrect(EXP_IN_RECT* exp_in_rect, LINE_TOKEN* line_token){
    int index = 1;
    int preIndexingPos = 0;
    int postIndexingPos = 0;
    int preIndexingExpr = 1;
    while(line_token->operands[index] != NULL){
        int length = (int) strlen(line_token->operands[index]);
        char firstChar = line_token->operands[index][0];
        char lastChar = line_token->operands[index][length - 1];
        if(firstChar == '[' && lastChar == ']'){
            preIndexingExpr = 0;
            line_token->operands[index]++;
            exp_in_rect->preIndexingExpr[preIndexingPos] = line_token->operands[index];
            preIndexingPos++;
        } else if(firstChar == '[' ){
            preIndexingExpr = 1;
            line_token->operands[index]++;
            exp_in_rect->preIndexingExpr[preIndexingPos] = line_token->operands[index];
            preIndexingPos++;
        } else if(lastChar == ']'){
            preIndexingExpr = 0;
            exp_in_rect->preIndexingExpr[preIndexingPos] = line_token->operands[index];
            preIndexingPos++;
        } else if(preIndexingExpr){
            exp_in_rect->preIndexingExpr[preIndexingPos] = line_token->operands[index];
            preIndexingPos++;
        }
        else {
            exp_in_rect->preIndexingExpr[postIndexingPos] = line_token->operands[postIndexingPos];
            postIndexingPos++;
        }
        index++;
    }
    exp_in_rect->numOfPreIndexingExpr = preIndexingPos;
    exp_in_rect->numOfPostIndexingExpr = postIndexingPos;
}
u32 shifting1(LINE_TOKEN* line_token, int i){
    u32 operand2 = 0;
    operand2 += parseRegister(line_token->operands[i]);
    /*printf(line_token->operands[i+1]);
    printf("\n");*/
    if(line_token->numOfOperands > i + 1) {
        if (strcmp(line_token->operands[i + 1], "lsl") == 0) {

        } else if (strcmp(line_token->operands[i + 1], "lsr") == 0) {
            operand2 += 1 << 5;
        } else if (strcmp(line_token->operands[i + 1], "asr") == 0) {
            operand2 += 2 << 5;
        } else if (strcmp(line_token->operands[i + 1], "ror") == 0) {
            operand2 += 3 << 5;
        }

        if (line_token->operands[i + 2][0] == '#') {
            if (parseExpression(line_token->operands[i + 2]) > 0x1F) {
                printf("Error: shift integer too large\n");
            } else {
                operand2 += parseExpression(line_token->operands[i + 2]) << 7;
            }
        } else {
            operand2 += parseRegister(line_token->operands[i + 2]) << 8;
            operand2 += 1 << 4;
        }
    }
    return operand2;
}

void calculate2(LINE_TOKEN *line_token, int i, INSTRUCTION *instr) {

    if(line_token->operands[i][0] == '+' | line_token->operands[i][0] == '-'){
        if(line_token->operands[i][0] == '+'){
            instr->instr.sdt->U = 1;
        } else {
            instr->instr.sdt->U = 0;
        }
        line_token->operands[i]++;
        instr->instr.sdt->OFFSET=shifting1(line_token,i);
    } else {
        instr->instr.sdt->U = 1;
        instr->instr.sdt->OFFSET = shifting1(line_token,i);
    }
}

void calculate1(LINE_TOKEN *line_token, int i, INSTRUCTION *instr, u32 address, u32 numofinstr) {
    u32 operand2=0;
    u32 val;
    if(line_token -> operands[i][1] == '-'){
        line_token->operands[i]++;
        val = parseExpression(line_token->operands[i]);
        instr->instr.sdt->U = 0;
    }
    else {
        val = parseExpression(line_token->operands[i]);
        instr->instr.sdt->U = 1;
    }
    u32 rotate_value = 0;
    while(val > 0xff){
        if(rotate_value > 0xff){
            instr->instr.sdt->REGN=15;
            Memory[memoryPos] = parseExpression(line_token->operands[i]);
            val = (numofinstr + memoryPos)*4 - address - 8;
            memoryPos++;
            rotate_value = 0;
            printf("Error: can fit the number in 8 bit\n");
            break;
        }
        /*printf("Before ");
        printBit(val);*/
        val = RotateR(val,30);
        rotate_value+=1;
        /*printf("After  ");
        printBit(val);
        printf("\n");*/
        while((val&3)==0){
            val = RotateR(val,30);
            rotate_value+=1;
        }
    }
    /*while((val&3)==0){
        val = RotateR(val,30);
        rotate_value+=1;
    }*/
    operand2 += val;
    operand2 += rotate_value << 8;
    instr->instr.sdt->OFFSET = operand2;
}

void assembleLdr(LINE_TOKEN *line_token, INSTRUCTION *instr, u32 address, u32 numOfInstructions) {

    //Set the type of instruction as single data transfer
    strcpy(instr->type,"singledatatransfer");
    //allocate memory for instr->instr.sdt
    instr->instr.sdt = malloc(sizeof(SIN_DATA_TRAN_INSTR));

    // set opcode, destination register and also L flag
    strcpy(instr->instr.sdt->OPCODE,"ldr");
    // Condition sets as 1110 meaning the instruction always executes
    instr->instr.sdt->COND = 0xe;
    // Destination register set
    instr->instr.sdt->REGD = parseRegister(line_token->operands[0]);
    // Representing load instruction
    instr->instr.sdt->L = 1;

    if (line_token->operands[1][0] == '='){
        // Instruction is in the form of ldr Rn, <=expression>
        if(parseExpression(line_token->operands[1]) <= 0xff){
            //if the expression is less than 0xff a mov instruction is carried out
            line_token->operands[1][0] = '#';
            strcpy(line_token->str.opcode, "mov");
            assembleMov(line_token, instr);
        } else {
            instr->instr.sdt->REGN=15;
            Memory[memoryPos] = parseExpression(line_token->operands[1]);
            printf("numOfInstructions = %d, memoryPos = %d, address = %d", numOfInstructions, memoryPos, address);
            instr->instr.sdt->U = 1;
            u32 val = (numOfInstructions + memoryPos) * 4 - address - 8;
            if(val <= 0xff){
                instr->instr.sdt->OFFSET = val;
            }
            else{
                u32 rotate_value = 0 ;
                while(val > 0xff){
                    if(rotate_value > 0xff){
                        printf("Error: can fit the number in 8 bit\n");
                        break;
                    }
                    val = RotateR(val,30);
                    rotate_value+=1;
                    while((val&3)==0){
                        val = RotateR(val,30);
                        rotate_value+=1;
                    }
                }
                instr->instr.sdt->OFFSET = val;
                instr->instr.sdt->OFFSET += rotate_value << 8;
            }
            memoryPos++;
            // Flag for pre-Indexing set
            instr->instr.sdt->P = 1;
        }
    } else {
        // Allocate memory to the structure for parsing operands with square brackets ([])
        EXP_IN_RECT *exp_in_rect = malloc(sizeof(EXP_IN_RECT));
        // Parsing the tokens to the structure
        parseExpressioninrect(exp_in_rect, line_token);

        // The instruction bits for the base register is assembled using the parseRegister function
        instr->instr.sdt->REGN   = parseRegister(line_token->operands[1]);
        // postIndexingCount stores the number of expressions after the address in the form of [Rn]
        int postIndexingCount = exp_in_rect->numOfPostIndexingExpr;
        // postIndexingCount stores the number of expressions in the address in
        int preIndexingCount  = exp_in_rect->numOfPreIndexingExpr;

        if(postIndexingCount == 0 && preIndexingCount == 1){
            // Expression is in the form of [Rn]
            instr->instr.sdt->REGN   = parseRegister(exp_in_rect->preIndexingExpr[0]);
//            printf(exp_in_rect->preIndexingExpr[0]);
            // Offset is set to 0
            instr->instr.sdt->OFFSET = 0;
            // Representing pre-Indexing instruction
            instr->instr.sdt->I = 0;
            instr->instr.sdt->P = 1;
            instr->instr.sdt->U = 1;
        } else if(postIndexingCount == 0 && preIndexingCount >= 2){
            // Expression is in the form of [Rn, <#expression>] or [Rn, {+/-}Rm{,<shift>}]
            if(line_token->operands[2][0]=='#') {
                // Expression is in the form of [Rn, <#expression>]
                // Immediate value is used
                instr->instr.sdt->I = 0;
                calculate1(line_token, 2, instr, address, numOfInstructions);
            } else {
                // Expression is in the form of [Rn, {+/-}Rm{,<shift>}]
                // Shifted register is used
                instr->instr.sdt->I = 1;
                calculate2(line_token, 2, instr);
            }
            // Representing pre-Indexing instruction
            instr->instr.sdt->P = 1;
        } else if(postIndexingCount >= 1 && preIndexingCount == 1){
            // Expression is in the form of [Rn], <#expression> or [Rn], {+/-}Rm{,<shift>}
            instr->instr.sdt->REGN = parseRegister(line_token->operands[1]);
            if(line_token->operands[2][0] == '#') {
                // Expression is in the form of [Rn], <#expression>
                // Immediate value is used
                instr->instr.sdt->I = 0;
                calculate1(line_token, 2, instr, address, numOfInstructions);
            } else {
                // Expression is in the form of [Rn], {+/-}Rm{,<shift>}
                // Shifted register is used
                instr->instr.sdt->I = 1;
                calculate2(line_token, 2,instr);
            }
            // Representing post-Indexing instruction
            instr->instr.sdt->P = 0;
        }
    }
}

//finish the parts which is not optional
void assembleStr(LINE_TOKEN *line_token, INSTRUCTION *instr, u32 address, u32 numOfInstructions) {

    // Set the type of instruction as single data transfer
    strcpy(instr->type,"singledatatransfer");
    // allocate memory for instr->instr.sdt
    instr->instr.sdt = malloc(sizeof(SIN_DATA_TRAN_INSTR));

    // set opcode, destination register and also L flag
    strcpy(instr->instr.sdt->OPCODE,"str");
    // Condition sets as 1110 meaning the instruction always executes
    instr->instr.sdt->COND = 0xe;

    instr->instr.sdt->REGD = parseRegister(line_token->operands[0]);
    // Load bit set to 0 meaning the storing instruction is carried out
    instr->instr.sdt->L = 0;
    instr->instr.sdt->U = 1;

    // Allocate memory to the structure for parsing operands with square brackets ([])
    EXP_IN_RECT *exp_in_rect = malloc(sizeof(EXP_IN_RECT));
    // Parsing the tokens to the structure
    parseExpressioninrect(exp_in_rect, line_token);

    // postIndexingCount stores the number of expressions after the address in the form of [Rn]
    int postIndexingCount = exp_in_rect->numOfPostIndexingExpr;
    // postIndexingCount stores the number of expressions in the address in
    int preIndexingCount  = exp_in_rect->numOfPreIndexingExpr;

    if(postIndexingCount == 0 && preIndexingCount == 1){
        // Expression is in the form of [Rn]
        instr->instr.sdt->I = 0;
        instr->instr.sdt->REGN = parseRegister(line_token->operands[1]);
        // Offset is set to 0
        instr->instr.sdt->OFFSET = 0;
        instr->instr.sdt->P = 1;
        instr->instr.sdt->U = 1;
    } else if(postIndexingCount == 0 && preIndexingCount >= 2){
        // Expression is in the form of [Rn, <#expression>] or [Rn, {+/-}Rm{,<shift>}]
        instr->instr.sdt->I = 1;
        instr->instr.sdt->REGN=parseRegister(line_token->operands[1]);
        if(line_token->operands[2][0]=='#') {
            // Expression is in the form of [Rn, <#expression>]
            // Immediate value is used
            instr->instr.sdt->I = 0;
            calculate1(line_token, 2, instr, address, numOfInstructions);
        } else {
            // Expression is in the form of [Rn, {+/-}Rm{,<shift>}]
            // Shifted register is used
            instr->instr.sdt->I = 1;
            calculate2(line_token, 2, instr);
        }
        // Representing pre-Indexing instruction
        instr->instr.sdt->P = 1;
    } else if(postIndexingCount >= 1 && preIndexingCount == 1){
        // Expression is in the form of [Rn], <#expression> or [Rn], {+/-}Rm{,<shift>}
        instr->instr.sdt->REGN = parseRegister(line_token->operands[1]);
        if(line_token->operands[2][0] == ' #') {
            // Expression is in the form of [Rn], <#expression>
            // Immediate value is used
            instr->instr.sdt->I = 0;
            calculate1(line_token, 2, instr, address, numOfInstructions);
        }
        else{
            // Expression is in the form of [Rn], {+/-}Rm{,<shift>}
            // Shifted register is used
            instr->instr.sdt->I = 1;
            calculate2(line_token, 2, instr);
        }
        // Representing post-Indexing instruction
        instr->instr.sdt->P = 0;
    }
}


/*
 * typedef struct sdt{
    u32 INSTRUCTION;
    char OPCODE[4];
    u32 COND: 4;
    u32 REGD;
    u32 REGN;
    u32 OFFSET;
    u32 I: 1;
    u32 P: 1;
    u32 U: 1;
    u32 L: 1;
}SIN_DATA_TRAN_INSTR;
 */