//
// Created by Timothy Cheuk on 06/06/2017.
//
/*
INSTRUCTION* branch (LINE_TOKEN* token){
    INSTRUCTION* instr = malloc(sizeof(INSTRUCTION));
    BRANCH_INSTR* br = malloc (sizeof(BRANCH_INSTR));

    switch(token->opcode){

        case "beq":
            br->cond= 0x0;
            break;
        case "bne":
            br->cond= 0x1;
            break;
        case "bge":
            br->cond= 0xA;
            break;
        case "blt":
            br->cond= 0xB;
            break;
        case "bgt":
            br->cond= 0xC;
            break;
        case "ble":
            br->cond= 0xD;
            break;
        case "bal":
            br->cond= 0xE;
            break;
        case "b":
            br->cond= 0xE;
            break;
        default:
            printf("Error: no suffix found");
            break;

    }







    instr->type = "branch";
    instr->instr = br;
    return instr;
}
*/

void assembleBeq(LINE_TOKEN* line_token, INSTRUCTION* instr)
{
    strcopy(instr->instr.br->OPCODE,"beq");
    instr->instr.br->COND = 0x0;

}
void assembleBne(LINE_TOKEN* line_token, INSTRUCTION* instr){
    strcopy(instr->instr.br->OPCODE,"bne");
    instr->instr.br->COND = 0x1;
}
void assembleBge(LINE_TOKEN* line_token, INSTRUCTION* instr)
{
    strcopy(instr->instr.br->OPCODE,"bge");
    instr->instr.br->COND = 0xA;
}
void assembleBlt(LINE_TOKEN* line_token, INSTRUCTION* instr){
    strcopy(instr->instr.br->OPCODE,"blt");
    instr->instr.br->COND = 0xB;
}
void assembleBgt(LINE_TOKEN* line_token, INSTRUCTION* instr){
    strcopy(instr->instr.br->OPCODE,"bgt");
    instr->instr.br->COND = 0xC;
}
void assembleBle(LINE_TOKEN* line_token, INSTRUCTION* instr){
    strcopy(instr->instr.br->OPCODE,"ble");
    instr->instr.br->COND = 0xD;
}
void assembleB(LINE_TOKEN* line_token, INSTRUCTION* instr){
    strcopy(instr->instr.br->OPCODE,"by");
    instr->instr.br->COND = 0xE;
}

/*typedef struct br{
u32 INSTRUCTION;
char OPCODE[4];
u32 COND: 4;
u32 OFFSET;
}BRANCH_INSTR;


 typedef struct{
    enum TOKEN_TYPE type;
    char label[512];
    char opcode[4];
    char *operands[10];
    int numOfOperands;
}LINE_TOKEN;

 */
