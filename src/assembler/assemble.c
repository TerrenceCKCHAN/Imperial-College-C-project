#include "assemble.h"
#include "tokenizer.h"

void binaryFileWriter(u32 instr[], char ** argv){
    FILE *ofp = fopen(argv[1],"wb");
    if(ofp == NULL){
        fprintf(stderr,"Unable to write file");
        exit(EXIT_FAILURE);
    }

    fwrite(instr,sizeof(instr),1,ofp);
}



int main(int argc, char **argv){
   // struct Linkedlist* list = getNewlist();
   // list = insertElementInNode(list, "kokok",3);


  return EXIT_SUCCESS;
}

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

struct Linkedlist* insertElementInNode(struct Linkedlist* list,char *key,void* value){     //insert element in the head return the new linked list
    struct Linkedlist* newlist = getNewlist();
    newlist->key = key;
    newlist->value = value;
    if(list==NULL){
        return newlist;
    }else{
        newlist->next = list;
        list = newlist;
    }
    return list;
};




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

char* lookUpkey(struct Linkedlist *list, void* value){
    struct Linkedlist* current =list;
    while(current->value!=value){
        current = current->next;
        if(current==NULL){
            printf("No such value");
            return NULL;
        }
    }
    return current->key;
}