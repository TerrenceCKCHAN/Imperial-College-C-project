#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <limits.h>



typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;


/*This is use to set and get the flag of the CPSR register*/
#define NFLAG_MASK (u32) 1 << 31
#define ZFLAG_MASK (u32) 1 << 30
#define CFLAG_MASK (u32) 1 << 29
#define VFLAG_MASK (u32) 1 << 28

#define SET_NFLAG(x) (u32) (x << 31 & NFLAG_MASK)
#define SET_ZFLAG(x) (u32) (x << 30 & ZFLAG_MASK)
#define SET_CFLAG(x) (u32) (x << 29 & CFLAG_MASK)
#define SET_VFLAG(x) (u32) (x << 28 & VFLAG_MASK)

#define GET_NFLAG(x) (u32) (SET_NFLAG(x)>>31)
#define GET_ZFLAG(x) (u32) (SET_ZFLAG(x)>>30)
#define GET_CFLAG(x) (u32) (SET_CFLAG(X)>>29)
#define GET_VFLAG(x) (u32) (SET_VFLAG(x)>>28)



/*This is use to extract bit 26 and 27 in the instruction set*/
#define BIT2627_MASK             (u32)   0x3u<<26
#define FIND_BIT2627(x)          (u32)   (BIT2627_MASK & x)>>26

/*To determine which state the instruction set are*/
#define IS_MULTI(x)              (u32)   ((0x90u & x)==0x90)&(FIND_BIT2627(x)==0)
#define IS_DATAPROCESS(x)        (u32)   ((FIND_BIT2627(x)==0) & !IS_MULTI(x)
#define IS_SINDATATRAN(x)        (u32)   FIND_BIT2627(x) == 0x1u
#define IS_BRANCH(x)             (u32)   FIND_BIT2627(x) == 0x2u

/*This is the masks, setter and getter for data processing instruction (for testing purpose) */
#define COND_MASK            (u32)         0xFu<<28
#define IMMED_OP_MASK        (u32)         0x1u<<24
#define OP_CODE_MASK         (u32)         0xFu<<20
#define S_MASK               (u32)         0x1u<<19
#define FIRST_OP_REG_MASK    (u32)         0xFu<<15
#define DIS_REG_MASK         (u32)         0xFu<<11

#define SET_COND(x)              (u32)          (x << 28 & COND_MASK)
#define SET_IMMED_OP             (u32)          (x << 24 & IMMED_OP_MASK)
#define SET_OP_CODE(x)           (u32)          (x << 20 & OP_COND_MASK)
#define SET_S(x)                 (u32)          (x << 19 & S_MASK)
#define SET_FIRST_OP_REG(x)      (u32)          (x << 15 & FIRST_OP_REG_MASK)
#define SET_DIS_REG(x)           (u32)          (x <<11 & DIS_REG_MASK)
#define SET_OPRAND2(x)           (u32)          (x)

#define GET_COND(x)              (u32)          SET_COND(x)>>28
#define GET_IMMED_OP(x)          (u32)          SET_IMMED_OP_MASK(x)>>24
#define GET_OP_CODE(x)           (u32)          SET_OP_CODE(x)>>20
#define GET_S(x)                 (u32)          SET_S(x)>>19
#define GET_FIRST_OP_REG(x)      (u32)          SET_FIRST_OP_REG_MASK(x)>>15
#define GET_DIS_REG(x)           (u32)          SET_DIS_REG_MASK(x)>>11
#define GET_OPRAND2(x)           (u32)          SET_OPRAND2(x)


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
    uint32_t mask = 1 << 31;
    for(i = 0;i < 32;++i){
        printf("%i", (x & mask) != 0);
        x<<=1;
    }
    printf("\n");
}

void loadbinaryFile(char* address){
    unsigned char *combuffer;
    u32 size;
    FILE *ifp;

    ifp = fopen(address, "rb");

    fseek(ifp, 0, SEEK_END);
    size = ftell(ifp);
    fseek(ifp, 0, SEEK_SET);
    combuffer = (unsigned char *) malloc(size);
    combuffer = malloc(size);

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




int main(int argc,  char **argv) {
    char address[400];
    strcpy(address, "/homes/hxm16/arm_1617_testsuite/test_cases/add01");
    printBit(GET_COND(0xCu));
  return EXIT_SUCCESS;
}









