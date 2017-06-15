/////////////////////////////////////////////////////////////////////////////////////////
//C Group Project - First Year (2016-2017)
//File: ADT_linkedlist.c
//Group: 6
//Member: Cheung, Ka (klc116), Mang, Hao (hxm16), Cheuk, Ki (kfc216), Chan, Chun (ckc116)
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
//  Linked List Abstract Data Type
//  key = labels in the assembler program
//  value = address of the labels
//  PRE: Valid label and its corresponding address is inserted in the head of linked list
//  POST:labels can be searched and return its address using lookUpValue Function
/////////////////////////////////////////////////////////////////////////////////////////
#include "assemble.h"

struct Linkedlist* getNewlist(void){
    struct Linkedlist* list = malloc(sizeof(struct Linkedlist));
    if(list == NULL){
        perror("getNewList");
        exit(EXIT_FAILURE);
    }
    list->value = NOT_EXIST;
    list->key = NULL;
    list->next = NULL;
    return list;
}

void insertElement(struct Linkedlist **list, char *key, u32 value){
    struct Linkedlist* newlist = getNewlist();
    newlist->key = key;
    newlist->value = value;
    newlist->next = *list;
    *list = newlist;
}

u32 lookUpValue(struct Linkedlist *list, char *key){
    struct Linkedlist* current =list;
    while(strcmp(current->key,key)!=0){
        current = current->next;
        if(current==NULL){
            printf("No such key");
            exit(EXIT_FAILURE);
        }
    }
    return current->value;
}

void printLinkedList(struct Linkedlist* linkedlist){
    struct Linkedlist*iter =linkedlist;
    while(iter->next != NULL){
        printf("key = %s \t", iter->key);
        printf("value = %d \n", (u32) iter->value);
        iter = iter->next;
    }
    printf("\n");
}