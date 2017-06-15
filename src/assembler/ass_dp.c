/////////////////////////////////////////////////////////////////////////////////////////
//C Group Project - First Year (2016-2017)
//File: ass_dp.c
//Group: 6
//Member: Cheung, Ka (klc116), Mang, Hao (hxm16), Cheuk, Ki (kfc216), Chan, Chun (ckc116)
/////////////////////////////////////////////////////////////////////////////////////////
#include "assemble.h"
#include "parser.h"

/*typedef struct {
    u32 INSTRUCTION;
    char OPCODE[4];
    u32 COND: 4;
    u32 S:1;
    u32 I:1;
    u32 DEST;
    u32 SRC;
    u32 OPERAND2;
}DATAPROCESSING_INSTR;*/

//a helper function for transforming an expression to an immediate value operand
//the integer i state the relative position of where the <operand2> is starting
u32 imm_value(LINE_TOKEN *line_token, int i){
    //initialising the operand
    u32 operand2=0;
    u32 Imm = parseExpression(line_token->operands[i]);
    u32 Rotate = 0;
    //a while loop for determining the Rotate and also Imm
    while(Imm>0xff){
        if(Rotate>0xff){
            printf("Error: cant fit the number in 8 bit\n");
            break;
        }
        /*printf("Before ");
        printBit(Imm);*/
//        Imm = RotateR(Imm,30);
        Imm = LShiftL(Imm,2);
        Rotate+=1;
        /*printf("After  ");
        printBit(Imm);
        printf("\n");*/
        while((Imm&3)==0){
//            Imm = RotateR(Imm,30);
            Imm = LShiftL(Imm,2);
            Rotate+=1;
        }
    }
    /*while((Imm&3)==0){
        Imm = RotateR(Imm,30);
        Rotate+=1;
    }*/
    //building the operand2
    operand2|=Imm;
    operand2|=Rotate<<8;
    return operand2;
}

//a helper function for transforming an expression to an shifted register operand
//the integer i state the relative position of where the <operand2> is starting
u32 shifting(LINE_TOKEN* line_token, int i){
    //initialising the operand
    u32 operand2=0;
    operand2+=parseRegister(line_token->operands[i]);
    /*printf(line_token->operands[i+1]);
    printf("\n");*/
    if(line_token->numOfOperands>i+1) {
        // building the shift type
        if (strcmp(line_token->operands[i + 1], "lsl") == 0) {

        } else if (strcmp(line_token->operands[i + 1], "lsr") == 0) {
            operand2 |= 1 << 5;
        } else if (strcmp(line_token->operands[i + 1], "asr") == 0) {
            operand2 |= 2 << 5;
        } else if (strcmp(line_token->operands[i + 1], "ror") == 0) {
            operand2 |= 3 << 5;
        } else {
            printf("Error: shift type not found\n");
        }

        if (line_token->operands[i + 2][0] == '#') {
            //if the shift value is a value
            if (parseExpression(line_token->operands[i + 2]) > 0x1F) {
                printf("Error: shift integer too large\n");
            } else {
                operand2 |= parseExpression(line_token->operands[i + 2]) << 7;
            }
        } else {
            //if the shift value is a register
            operand2 |= parseRegister(line_token->operands[i + 2]) << 8;
            operand2 |= 1 << 4;
        }
    }
    return operand2;
}


//assume the operand 2 is an immediate value for now. can be ammended to support shifting
//helper method to avoid duplication, instructions which use this helper include and, eor, sub, rsb, add, orr
void assemble_instr_that_compute_results(LINE_TOKEN* line_token, INSTRUCTION* instr) {
    instr->instr.dp = malloc(sizeof(DATAPROCESSING_INSTR));
    instr->instr.dp->DEST     = parseRegister(line_token->operands[0]);
    instr->instr.dp->SRC      = parseRegister(line_token->operands[1]);
    //determining if the <operand2> is an imm value or a shifting register, then call the helper function respectively
    if (line_token->operands[2][0]=='#') {
        instr->instr.dp->I=1;
        instr->instr.dp->OPERAND2= imm_value(line_token, 2);
    }
    else{
        instr->instr.dp->I=0;
        instr->instr.dp->OPERAND2 = shifting(line_token, 2);

    }
    instr->instr.dp->S        = 0;
    instr->instr.dp->COND     = 0xe;

}

void assembleAdd(LINE_TOKEN* line_token, INSTRUCTION* instr) {
    strcpy(instr->type, "dataprocessing");
    assemble_instr_that_compute_results(line_token, instr);
    strcpy(instr->instr.dp->OPCODE, "add");
    instr->instr.dp->OPCODEBIN = 0x4;


}

void assembleSub(LINE_TOKEN* line_token, INSTRUCTION* instr) {
    strcpy(instr->type, "dataprocessing");
    assemble_instr_that_compute_results(line_token, instr);
    strcpy(instr->instr.dp->OPCODE, "sub");
    instr->instr.dp->OPCODEBIN = 0x2;

}

void assembleRsb(LINE_TOKEN* line_token, INSTRUCTION* instr) {
    strcpy(instr->type, "dataprocessing");
    assemble_instr_that_compute_results(line_token, instr);
    strcpy(instr->instr.dp->OPCODE, "rsb");
    instr->instr.dp->OPCODEBIN = 0x3;

}

void assembleAnd(LINE_TOKEN* line_token, INSTRUCTION* instr) {
    strcpy(instr->type, "dataprocessing");
    assemble_instr_that_compute_results(line_token, instr);
    strcpy(instr->instr.dp->OPCODE, "and");
    instr->instr.dp->OPCODEBIN = 0x0;
}

void assembleEor(LINE_TOKEN* line_token, INSTRUCTION* instr) {
    strcpy(instr->type, "dataprocessing");
    assemble_instr_that_compute_results(line_token, instr);
    strcpy(instr->instr.dp->OPCODE, "eor");
    instr->instr.dp->OPCODEBIN = 0x1;
}

void assembleOrr(LINE_TOKEN* line_token, INSTRUCTION* instr) {
    strcpy(instr->type, "dataprocessing");
    assemble_instr_that_compute_results(line_token, instr);
    strcpy(instr->instr.dp->OPCODE, "orr");
    instr->instr.dp->OPCODEBIN = 0xc;
}

void assembleMov(LINE_TOKEN* line_token, INSTRUCTION* instr) {
//    printf("AssembleMov\n");
    strcpy(instr->type, "dataprocessing");
    instr->instr.dp = malloc(sizeof(DATAPROCESSING_INSTR));
    strcpy(instr->instr.dp->OPCODE, "mov");
    instr->instr.dp->DEST     = parseRegister(line_token->operands[0]);
    //determining if operand2 is an imm value or a shift register
    if (line_token->operands[1][0]=='#') {
        instr->instr.dp->I=1;
        instr->instr.dp->OPERAND2= imm_value(line_token, 1);

    }
    else{
        instr->instr.dp->I=0;
        instr->instr.dp->OPERAND2=shifting(line_token,1);
    }
    instr->instr.dp->SRC      = 0;
    instr->instr.dp->COND     = 0xe;
    instr->instr.dp->S        = 0;
    instr->instr.dp->OPCODEBIN = 0xd;
}
//helper method to avoid duplication, instructions which use this helper include tst, teq, cmp
void assemble_set_flag_instructions(LINE_TOKEN* line_token, INSTRUCTION* instr) {
    instr->instr.dp->SRC      = parseRegister(line_token->operands[0]);
    instr->instr.dp->DEST = 0;
    //determining if operand2 is an imm value or a shift register
    if (line_token->operands[1][0]=='#') {
        instr->instr.dp->I=1;
        instr->instr.dp->OPERAND2 = imm_value(line_token, 1);
    }
    else{
        instr->instr.dp->I=0;
        instr->instr.dp->OPERAND2=shifting(line_token,1);
    }
    instr->instr.dp->S        = 1;
    instr->instr.dp->COND     = 0xe;
}

void assembleTst(LINE_TOKEN* line_token, INSTRUCTION* instr) {
    strcpy(instr->type, "dataprocessing");
    instr->instr.dp = malloc(sizeof(DATAPROCESSING_INSTR));
    strcpy(instr->instr.dp->OPCODE, "tst");
    instr->instr.dp->OPCODEBIN = 0x8;
    assemble_set_flag_instructions(line_token, instr);
}

void assembleTeq(LINE_TOKEN* line_token, INSTRUCTION* instr) {
    strcpy(instr->type, "dataprocessing");
    instr->instr.dp = malloc(sizeof(DATAPROCESSING_INSTR));
    strcpy(instr->instr.dp->OPCODE, "teq");
    instr->instr.dp->OPCODEBIN = 0x9;
    assemble_set_flag_instructions(line_token, instr);
}

void assembleCmp(LINE_TOKEN* line_token, INSTRUCTION* instr) {
    strcpy(instr->type, "dataprocessing");
    instr->instr.dp = malloc(sizeof(DATAPROCESSING_INSTR));
    strcpy(instr->instr.dp->OPCODE, "cmp");
    instr->instr.dp->OPCODEBIN = 0xa;
    assemble_set_flag_instructions(line_token, instr);
}

void assembleAndeq(LINE_TOKEN* line_token, INSTRUCTION* instr) {
    strcpy(instr->type, "dataprocessing");
    instr->instr.dp = malloc(sizeof(DATAPROCESSING_INSTR));
    strcpy(instr->instr.dp->OPCODE, "stp");
    instr->instr.dp->COND = 0;
    instr->instr.dp->DEST = 0;
    instr->instr.dp->I = 0;
    instr->instr.dp->OPCODEBIN = 0;
    instr->instr.dp->OPERAND2 = 0;
    instr->instr.dp->S = 0;
    instr->instr.dp->SRC = 0;
}
