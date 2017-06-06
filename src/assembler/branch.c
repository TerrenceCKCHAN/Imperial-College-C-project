//
// Created by Timothy Cheuk on 06/06/2017.
//
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
