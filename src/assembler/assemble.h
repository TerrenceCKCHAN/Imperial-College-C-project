#ifndef ARM11_06_ASSEMBLE_H
#define ARM11_06_ASSEMBLE_H

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <string.h>

typedef uint32_t u32;

typedef int (bst_compare_t) (void* , void*);


struct Linkedlist{
    struct Linkedlist *next;
    void* value;
    char *key;
};


struct Linkedlist* getNewlist(void);
struct Linkedlist* insertElementInNode(struct Linkedlist* list,char *key, void* value);
void* lookUpValue(struct Linkedlist *list, char *key);
char* lookUpkey(struct Linkedlist *list, void* value);







#endif //ARM11_06_ASSEMBLE_H
