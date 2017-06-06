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
    while(linkedlist->next != NULL){
        printf("key = %s \t", linkedlist->key);
        printf("value = %d \n", (u32) linkedlist->value);
        linkedlist = linkedlist->next;
    }
}

