/////////////////////////////////////////////////////////////////////////////////////////
//C Group Project - First Year (2016-2017)
//File.assemble.h
//Group: 6
//Member: Cheung, Ka (klc116), Mang, Hao (hxm16), Cheuk, Ki (kfc216), Chan, Chun (ckc116)
/////////////////////////////////////////////////////////////////////////////////////////
#ifndef ARM11_06_ASSEMBLE_H
#define ARM11_06_ASSEMBLE_H

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <string.h>
#include "tokenizer.h"
#include "../emulator/instruction.h"



typedef uint32_t u32;
/////////////////////////////////////////////////////////////////////////////////////////
//  Linked List Abstract Data Type
/////////////////////////////////////////////////////////////////////////////////////////
struct Linkedlist{
    struct Linkedlist *next;
    void* value;
    char *key;
}*head;

struct Linkedlist* getNewlist(void);
void* lookUpValue(struct Linkedlist *list, char *key);
char* lookUpkey(struct Linkedlist *list, void* value);
void printLinkedList(struct Linkedlist* linkedlist);
void insertElement(struct Linkedlist** list, char *key, void* value);
/////////////////////////////////////////////////////////////////////////////////////////
//  Binary Search Tree Abstract Data Type
/////////////////////////////////////////////////////////////////////////////////////////
typedef int (*bst_compare_t)(void*, void*);

typedef struct BST_node{
    char * key;
    void * value;
    struct BST_node* left;
    struct BST_node* right;
}BST_node;


typedef struct BST{
    bst_compare_t compare;
    BST_node *root;
}BST;

struct BST* getNewinitTree(bst_compare_t compare);
struct BST_node* insertToNode(BST_node* node, char* key, void* value, bst_compare_t compare);
void insertElem(struct BST* tree, char* key, void* value, bst_compare_t compare);
void* bst_lookUpValue_elem(BST_node* node, char* key, bst_compare_t compare);
void* bst_lookUpValue(struct BST* tree, char* key,bst_compare_t compare);
int stringcmp(char* s1, char* s2);
void printBST_node(BST_node* node);
void printBST(struct BST* tree);
void bst_destroy_elem(struct BST_node * node);
void bst_destroy(struct BST* tree);
/////////////////////////////////////////////////////////////////////////////////////////



struct table{
    char* opcode;
    void (*func)(LINE_TOKEN*, INSTRUCTION*);
};

struct branchelem{
    char* opcode;
    void (*func)(LINE_TOKEN*, INSTRUCTION*, struct Linkedlist*);
};



void assembleAdd(LINE_TOKEN* line_token, INSTRUCTION* instr);
void assembleSub(LINE_TOKEN* line_token, INSTRUCTION* instr);
void assembleRsb(LINE_TOKEN* line_token, INSTRUCTION* instr);
void assembleAnd(LINE_TOKEN* line_token, INSTRUCTION* instr);
void assembleEor(LINE_TOKEN* line_token, INSTRUCTION* instr);
void assembleOrr(LINE_TOKEN* line_token, INSTRUCTION* instr);
void assembleMov(LINE_TOKEN* line_token, INSTRUCTION* instr);
void assembleTst(LINE_TOKEN* line_token, INSTRUCTION* instr);
void assembleTeq(LINE_TOKEN* line_token, INSTRUCTION* instr);
void assembleCmp(LINE_TOKEN* line_token, INSTRUCTION* instr);
void assembleMul(LINE_TOKEN* line_token, INSTRUCTION* instr);
void assembleMla(LINE_TOKEN* line_token, INSTRUCTION* instr);
void assembleLdr(LINE_TOKEN* line_token, INSTRUCTION* instr);
void assembleStr(LINE_TOKEN* line_token, INSTRUCTION* instr);
/*void assembleBeq(LINE_TOKEN* line_token, INSTRUCTION* instr, struct Linkedlist *symboltable);
void assembleBne(LINE_TOKEN* line_token, INSTRUCTION* instr, struct Linkedlist *symboltable);
void assembleBge(LINE_TOKEN* line_token, INSTRUCTION* instr, struct Linkedlist *symboltable);
void assembleBlt(LINE_TOKEN* line_token, INSTRUCTION* instr, struct Linkedlist *symboltable);
void assembleBgt(LINE_TOKEN* line_token, INSTRUCTION* instr, struct Linkedlist *symboltable);
void assembleBle(LINE_TOKEN* line_token, INSTRUCTION* instr, struct Linkedlist *symboltable);
void assembleB(LINE_TOKEN* line_token, INSTRUCTION* instr, struct Linkedlist *symboltable);*/
void assembleLsl(LINE_TOKEN* line_token, INSTRUCTION* instr);
void assembleAndeq(LINE_TOKEN* line_token, INSTRUCTION* instr);



typedef void(*assemblefunction)(LINE_TOKEN*, INSTRUCTION*);
typedef void(*assembleBranch)(LINE_TOKEN*, INSTRUCTION*, struct Linkedlist* symbolTable);
assemblefunction lookUpfunction(char* instr);
assembleBranch lookUpBranch(char* instr);
u32 assembleInstructions(INSTRUCTION* instr);
void printBit1(uint32_t x);
u32 secondpass(LINE_TOKEN* line_tokens[], u32* Memory,struct Linkedlist **symbolTable, int numOfLines);


#endif //ARM11_06_ASSEMBLE_H
