//
// Created by Timothy Cheuk on 06/06/2017.
//

u32 transformnum(u32 num){
    u32 val;
    if ( num >0 ){
        val+=(num>>2);
    }
    else if(num<0){
        val+=1<<24;
        val+=~(num>>2);
    }
    returm val;
}

//as by the time i finish this part we still not able to get current address, create this helper so we can amend easier
void generalbr(LINE_TOKEN* line_token, INSTRUCTION* instr,struct Linkedlist *symboltable){
    u32 i = (u32) lookUpValue(symboltable,line_token->operands[0]);
    instr->instr.br->OFFSET = transformnum(i);
}


void assembleBeq(LINE_TOKEN* line_token, INSTRUCTION* instr,struct Linkedlist *symboltable){
    strcopy(instr->instr.br->OPCODE,"beq");
    instr->instr.br->COND = 0x0;
    generalbr(line_token, instr,symboltable);
}
void assembleBne(LINE_TOKEN* line_token, INSTRUCTION* instr,struct Linkedlist *symboltable){
    strcopy(instr->instr.br->OPCODE,"bne");
    instr->instr.br->COND = 0x1;
    generalbr(line_token, instr,symboltable);
}
void assembleBge(LINE_TOKEN* line_token, INSTRUCTION* instr,struct Linkedlist *symboltable) {
    strcopy(instr->instr.br->OPCODE,"bge");
    instr->instr.br->COND = 0xA;
    generalbr(line_token, instr,symboltable);
}
void assembleBlt(LINE_TOKEN* line_token, INSTRUCTION* instr,struct Linkedlist *symboltable){
    strcopy(instr->instr.br->OPCODE,"blt");
    instr->instr.br->COND = 0xB;
    generalbr(line_token, instr,symboltable);
}
void assembleBgt(LINE_TOKEN* line_token, INSTRUCTION* instr,struct Linkedlist *symboltable){
    strcopy(instr->instr.br->OPCODE,"bgt");
    instr->instr.br->COND = 0xC;
    generalbr(line_token, instr,symboltable);
}
void assembleBle(LINE_TOKEN* line_token, INSTRUCTION* instr,struct Linkedlist *symboltable){
    strcopy(instr->instr.br->OPCODE,"ble");
    instr->instr.br->COND = 0xD;
    generalbr(line_token, instr,symboltable);
}
void assembleB(LINE_TOKEN* line_token, INSTRUCTION* instr,struct Linkedlist *symboltable){
    strcopy(instr->instr.br->OPCODE,"bal");
    instr->instr.br->COND = 0xE;
    generalbr(line_token, instr,symboltable);
}
void assembleB(LINE_TOKEN* line_token, INSTRUCTION* instr,struct Linkedlist *symboltable){
    printf("hi");
    strcopy(instr->instr.br->OPCODE,"b");
    instr->instr.br->COND = 0xE;
    generalbr(line_token, instr,symboltable);
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
