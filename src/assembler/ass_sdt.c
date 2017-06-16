/////////////////////////////////////////////////////////////////////////////////////////
//C Group Project - First Year (2016-2017)
//File: ass_sdt.c
//Group: 6
//Member: Cheung, Ka (klc116), Mang, Hao (hxm16), Cheuk, Ki (kfc216), Chan, Chun (ckc116)
/////////////////////////////////////////////////////////////////////////////////////////
#include "assemble.h"

/////////////////////////////////////////////////////////////////////////////////////////
// Helper function for determining different case if the address is not a numeric value
// Address struct in assemble.h
/////////////////////////////////////////////////////////////////////////////////////////
void parse_address(ADDRESS *address, LINE_TOKEN *line_token){
    //the index for counting where the loop is when looping through the array of operands ,as address always start at operands[1], it is initialised as 1
    int index = 1;
    //number of expressions in  bracket
    int NumInBracket = 0;
    //num of expressions in bracket
    int NumNotInBracket = 0;
    //whether the exp is in a bracket or not, if it is in, set to 1, if not, set to 0, initialise as 1 as for all case, the first exp is in a bracket
    int inBracket = 1;
    //loop through the rest of the operands and check whether the expression is in bracket or not
    while(line_token->operands[index] != NULL){
        int length = (int) strlen(line_token->operands[index]);
        char firstChar = line_token->operands[index][0];
        char lastChar = line_token->operands[index][length - 1];

        if(firstChar == '[' && lastChar == ']'){
            //if it starts with '[' then it is in a bracket, the next will not be in a bracket tho as it ends with a ']',
            //no case have more than one bracket
            inBracket = 0;
            line_token->operands[index]++;
            address->Opr_in_Bracket[NumInBracket] = line_token->operands[index];
            NumInBracket++;
        } else if(firstChar == '[' ){
            //next one will still be in bracket
            inBracket = 1;
            line_token->operands[index]++;
            address->Opr_in_Bracket[NumInBracket] = line_token->operands[index];
            NumInBracket++;
        } else if(lastChar == ']'){
            //next one will not be in bracket, but the current one is
            inBracket = 0;
            address->Opr_in_Bracket[NumInBracket] = line_token->operands[index];
            NumInBracket++;
        } else if(inBracket){
            //if the previous one is ib bracket and is not end with ']', this one is in as well
            address->Opr_in_Bracket[NumInBracket] = line_token->operands[index];
            NumInBracket++;
        }
        else {
            //of previous one is not in, this one is not as well
            address->Opr_in_Bracket[NumNotInBracket] = line_token->operands[NumNotInBracket];
            NumNotInBracket++;
        }
        index++;
    }
    address->Num_Opr_in_bracket = NumInBracket;
    address->Num_Opr_not_in_bracket = NumNotInBracket;
}

/////////////////////////////////////////////////////////////////////////////////////////
// Setting up bit if there's a sign, then do the shifting using the shift in data processing
/////////////////////////////////////////////////////////////////////////////////////////
void shifting_with_sign(LINE_TOKEN *line_token, int i, INSTRUCTION *instr) {

    if((line_token->operands[i][0] == '+') | (line_token->operands[i][0] == '-')){
        if(line_token->operands[i][0] == '+'){
            instr->instr.sdt->U = 1;
        } else {
            instr->instr.sdt->U = 0;
        }
        line_token->operands[i]++;
        instr->instr.sdt->OFFSET = shifting(line_token, i);
    } else {
        instr->instr.sdt->U = 1;
        instr->instr.sdt->OFFSET = shifting(line_token, i);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////
//Approximately the same with the imm value in data processing, with few more exceptional case
/////////////////////////////////////////////////////////////////////////////////////////
void imm_value_sdt(LINE_TOKEN *line_token, int i, INSTRUCTION *instr, u32 address, u32 numofinstr) {
    u32 operand2 = 0;
    u32 val;
    //clearing up bit if there is a '-'
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
    //store to memory if too large
    while(val > 0xff){
        if(rotate_value > 0xff){
            instr->instr.sdt->REGN = 15;
            Memory[memoryPos] = parseExpression(line_token->operands[i]);
            val = (numofinstr + memoryPos) * 4 - address - 8;
            memoryPos++;
            rotate_value = 0;
            printf("Error: cant fit the number in 8 bit\n");
            break;
        }
        val = RotateR(val, 30);
        rotate_value++;
        while((val & 3) == 0){
            val = RotateR(val, 30);
            rotate_value++;
        }
    }
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
            //calculating the offset between the current address and the address where the memory is put
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
        ADDRESS *exp_in_rect = malloc(sizeof(ADDRESS));
        // Parsing the tokens to the structure
        parse_address(exp_in_rect, line_token);

        // The instruction bits for the base register is assembled using the parseRegister function
        instr->instr.sdt->REGN   = parseRegister(line_token->operands[1]);
        // postIndexingCount stores the number of expressions after the address in the form of [Rn]
        int postIndexingCount = exp_in_rect->Num_Opr_not_in_bracket;
        // postIndexingCount stores the number of expressions in the address in
        int preIndexingCount  = exp_in_rect->Num_Opr_in_bracket;

        if(postIndexingCount == 0 && preIndexingCount == 1){
            // Expression is in the form of [Rn]
            instr->instr.sdt->REGN   = parseRegister(exp_in_rect->Opr_in_Bracket[0]);
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
                imm_value_sdt(line_token, 2, instr, address, numOfInstructions);
            } else {
                // Expression is in the form of [Rn, {+/-}Rm{,<shift>}]
                // Shifted register is used
                instr->instr.sdt->I = 1;
                shifting_with_sign(line_token, 2, instr);
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
                imm_value_sdt(line_token, 2, instr, address, numOfInstructions);
            } else {
                // Expression is in the form of [Rn], {+/-}Rm{,<shift>}
                // Shifted register is used
                instr->instr.sdt->I = 1;
                shifting_with_sign(line_token, 2, instr);
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
    ADDRESS *exp_in_rect = malloc(sizeof(ADDRESS));
    // Parsing the tokens to the structure
    parse_address(exp_in_rect, line_token);

    // postIndexingCount stores the number of expressions after the address in the form of [Rn]
    int postIndexingCount = exp_in_rect->Num_Opr_not_in_bracket;
    // postIndexingCount stores the number of expressions in the address in
    int preIndexingCount  = exp_in_rect->Num_Opr_in_bracket;

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
            imm_value_sdt(line_token, 2, instr, address, numOfInstructions);
        } else {
            // Expression is in the form of [Rn, {+/-}Rm{,<shift>}]
            // Shifted register is used
            instr->instr.sdt->I = 1;
            shifting_with_sign(line_token, 2, instr);
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
            imm_value_sdt(line_token, 2, instr, address, numOfInstructions);
        }
        else{
            // Expression is in the form of [Rn], {+/-}Rm{,<shift>}
            // Shifted register is used
            instr->instr.sdt->I = 1;
            shifting_with_sign(line_token, 2, instr);
        }
        // Representing post-Indexing instruction
        instr->instr.sdt->P = 0;
    }
}