/////////////////////////////////////////////////////////////////////////////////////////
//C Group Project - First Year (2016-2017)
//File.ADT_linkedlist.c
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
    list->value =NULL;
    list->key =NULL;
    list->next =NULL;
    return list;
}





void insertElement(struct Linkedlist** list, char *key, void* value){
    struct Linkedlist* newlist = getNewlist();
    newlist->key = key;
    newlist->value = value;
    newlist->next = *list;
    *list = newlist;
}
/*TO be done
void insertElementLast(struct Linkedlist** list, char *key, void* value){
    struct Linkedlist* newlist = getNewlist();
    newlist->value = value;
    newlist->key = key;
    struct Linkedlist* current = *list;
    while(current->next->next != NULL){
        current = current->next;
    }
    current = newlist;

}
 */

void removeLast(struct Linkedlist **list){
    struct Linkedlist *current = *list;
    while(current->next->next!=NULL){
        current = current->next;
    }
    free(current);
}

void removeFirst(struct Linkedlist **list){
    struct Linkedlist* temp = *list;
    *list = temp->next;
    free(temp);
}




void* lookUpValue(struct Linkedlist *list, char *key){
    struct Linkedlist* current =list;
    while(strcmp(current->key,key)!=0){
        current = current->next;
        if(current==NULL){
            printf("No such key");
            return NULL;
        }
    }
    return current->value;
}

char* lookUpkey(struct Linkedlist *list, void* value) {
    struct Linkedlist *current = list;
    while (current->value != value) {
        current = current->next;
        if (current == NULL) {
            printf("No such value");
            return NULL;
        }
    }
    return current->key;
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

/*
int main(){
    struct Linkedlist* list = malloc(sizeof(struct Linkedlist));
    insertElement(&list,"a",3);
    insertElement(&list, "b",8);
    insertElement(&list, "c",4);
    insertElement(&list, "d",9);
    insertElement(&list, "e",7);

    printLinkedList(list);

}

*/
