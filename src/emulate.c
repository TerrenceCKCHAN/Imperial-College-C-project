#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <string.h>



typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;


/*This is use to set and get the flag of the CPSR register*/
#define NFLAG_MASK (u32) 1 << 31
#define ZFLAG_MASK (u32) 1 << 30
#define CFLAG_MASK (u32) 1 << 29
#define VFLAG_MASK (u32) 1 << 28

#define SET_NFLAG(x) (u32) (x  & NFLAG_MASK)
#define SET_ZFLAG(x) (u32) (x  & ZFLAG_MASK)
#define SET_CFLAG(x) (u32) (x  & CFLAG_MASK)
#define SET_VFLAG(x) (u32) (x  & VFLAG_MASK)

#define GET_NFLAG(x) (u32) (SET_NFLAG(x)>>31)
#define GET_ZFLAG(x) (u32) (SET_ZFLAG(x)>>30)
#define GET_CFLAG(x) (u32) (SET_CFLAG(X)>>29)
#define GET_VFLAG(x) (u32) (SET_VFLAG(x)>>28)

/*



/*This is use to extract bit 26 and 27 in the instruction set*/
#define BIT2627_MASK             (u32)   0x3u << 26
#define FIND_BIT2627(x)          (u32)   (BIT2627_MASK & x) >> 26

/*To determine which state the instruction set are*/
#define IS_MULTI(x)              (u32)   ((0x90u & x) == 0x90) & (FIND_BIT2627(x) == 0)
#define IS_DATAPROCESS(x)        (u32)   ((FIND_BIT2627(x) == 0) & !IS_MULTI(x)
#define IS_SINDATATRAN(x)        (u32)   FIND_BIT2627(x) == 0x1u
#define IS_BRANCH(x)             (u32)   FIND_BIT2627(x) == 0x2u

/*This is the masks, setter and getter for data processing instruction (for testing purpose) */

#define COND_MASK            (u32)         0xFu << 28
#define IMMED_OP_MASK        (u32)         0x1u << 25
#define OP_CODE_MASK         (u32)         0xFu << 21
#define S_MASK               (u32)         0x1u << 20
#define FIRST_OP_REG_MASK    (u32)         0xFu << 16
#define DIS_REG_MASK         (u32)         0xFu << 12

#define SET_COND(x)              (u32)          (x & COND_MASK)
#define SET_IMMED_OP(x)          (u32)          (x & IMMED_OP_MASK)
#define SET_OP_CODE(x)           (u32)          (x & OP_CODE_MASK)
#define SET_S(x)                 (u32)          (x & S_MASK)
#define SET_FIRST_OP_REG(x)      (u32)          (x & FIRST_OP_REG_MASK)
#define SET_DIS_REG(x)           (u32)          (x & DIS_REG_MASK)
#define SET_OPRAND2(x)           (u32)          (x)

#define GET_COND(x)              (u32)          SET_COND(x) >> 28
#define GET_IMMED_OP(x)          (u32)          SET_IMMED_OP(x) >> 25
#define GET_OP_CODE(x)           (u32)          SET_OP_CODE(x) >> 21
#define GET_S(x)                 (u32)          SET_S(x) >> 20
#define GET_FIRST_OP_REG(x)      (u32)          SET_FIRST_OP_REG(x) >> 16
#define GET_DIS_REG(x)           (u32)          SET_DIS_REG(x) >> 12
#define GET_OPRAND2(x)           (u32)          SET_OPRAND2(x)

/*define shifting operations*/
#define MSB              1 << 31
#define LShiftL(x,n)     x << n
#define LShiftR(x,n)     x >> n
#define AShiftR(x,n)     LShiftR(x, n)|(x & MSB)
#define RotateR(x,n)     (x>>n)|LShiftL(x, 32-n)





typedef struct{
    u32 COND:4;
    u32 I:1;
    u32 OPCODE:4;
    u32 S:1;
    u32 REGN:4;
    u32 REGD:4;
    u32 OPRAND2:12;
    }DATAPROCESSING;

typedef struct{
    u32 COND:4;
    u32 A:1;
    u32 S:4;
    u32 REGD:4;
    u32 REGN:4;
    u32 REGS:4;
    u32 REGM:4;
    }MULTIPLY;

typedef struct{
    u32 COND:4;
    u32 I:1;
    u32 P:1;
    u32 U:1;
    u32 L:1;
    u32 REGN:4;
    u32 REGD:4;
    u32 OFFSET:1;
    }SIN_DATA_TRAN;

typedef struct{
    u32 COND:4;
    u32 OFFSET:24;
    }BRANCH;

/*This is the function to print bit*/
void printBit(uint32_t x){
    int i;
    uint32_t mask = (uint32_t) 1 << 31;
    for(i = 0;i < 32;++i){
        printf("%i", (x & mask) != 0);
        x<<=1;
    }
    printf("\n");
}

void loadbinaryFile(char *address){
    unsigned char *combuffer;
    u32 size;
    FILE *ifp;

    ifp = fopen(address, "rb");

    fseek(ifp, 0, SEEK_END);
    size = (u32) ftell(ifp);
    fseek(ifp, 0, SEEK_SET);
    combuffer = (unsigned char *) malloc(size);

    if(ifp == NULL){
        fprintf(stderr,"Unable to read file!");
        exit(EXIT_FAILURE);
    }

    fread(combuffer, 1,size,ifp);

    for(int i = 0; i < size; i++) {
        printf("%x ",combuffer[i]);
        printBit(combuffer[i]);
        printf("\n");
    }

    fclose(ifp);
    free(combuffer);
}


u32 generateDataFromHex(char hex[]) {
    int length = strlen(hex);
    u32 data = 0;
    u32 shift = (length - 1) * 4;
    for (int pos = 0; pos < length; pos++) {
        u32 hexValue;
        if (hex[pos] >= '0' && hex[pos] <= '9') {
            hexValue = (hex[pos] - '0');
        } else if (hex[pos] >= 'a' && hex[pos] <= 'f') {
            hexValue = hex[pos] - 'a' + 10;
        }
        data += hexValue << shift;
        shift -= 4;
    }
    return data;

}

void DATAPROCESSING_INSTR(DATAPROCESSING *datapt){
    if((datapt->S)!=0){
        //TODO: change CPSR FLAG
    }
    //The CPSR register is unaffected

}

DATAPROCESSING DecodeDataProcessing(u32 instruction) {
    DATAPROCESSING instr;
    instr.COND     = GET_COND(instruction);
    instr.I        = GET_IMMED_OP(instruction);
    instr.OPCODE   = GET_OP_CODE(instruction);
    instr.S        = GET_S(instruction);
    instr.REGN     = GET_FIRST_OP_REG(instruction);
    instr.REGD     = GET_DIS_REG(instruction);
    instr.OPRAND2  = GET_OPRAND2(instruction);
    return instr;
}

void printStruct(DATAPROCESSING dp) {
    printf("COND %x\n",dp.COND);
    printf("I %x\n",dp.I);
    printf("OPCODE %x\n",dp.OPCODE);
    printf("S %x\n",dp.S);
    printf("REGN %x\n",dp.REGN);
    printf("REGD %x\n",dp.REGD);
    printf("OPRAND2 %x\n",dp.OPRAND2);
}

int main(int argc,  char **argv) {
    char hex[16];
    DATAPROCESSING dpstruct;
    printBit(0xFu<<11);
    scanf("%s", hex);
    printf("%x\n", generateDataFromHex(hex));
    u32 instruction = generateDataFromHex(hex);
    printBit(instruction);
    printStruct(DecodeDataProcessing(instruction));
    return EXIT_SUCCESS;
}


