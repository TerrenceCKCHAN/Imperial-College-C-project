#include "assemble.h"

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

struct BST* getNewinitTree(bst_compare_t compare){
    struct BST* tree = malloc(sizeof(struct BST));
    if(tree == NULL){
        perror("getNewTree");
        exit(EXIT_FAILURE);
    }
    tree->root = NULL;
    tree->compare = compare;
    return tree;
}



struct BST_node* insertToNode(BST_node* node, char* key, void* value, bst_compare_t compare){
    BST_node * newNode = malloc(sizeof(BST_node));
    newNode->key = key;
    newNode->value = value;
    if(node == NULL){
        return newNode;
    }else{
        int comparison = compare(key,node->key);
        if(comparison <= 0){                                           //if the value insert is less than or equal to current node, insert to left
            node->left=insertToNode(node->left, key,value,compare);
            return node;
        }else{
            node->right = insertToNode(node->right, key,value,compare); //if the value insert is larger to current node, insert to left
            return node;
        }
    }
}

void insertElem(struct BST* tree, char* key, void* value, bst_compare_t compare){
    tree->root = insertToNode(tree->root,key,value,compare);
}



void* bst_lookUpValue_elem(BST_node* node, char* key, bst_compare_t compare){
    BST_node * current = node;
    if(current!= NULL) {
        if (compare(current->key, key) == 0) {
            return current->value;
        } else if (compare(current->key,key) > 0) {
            return bst_lookUpValue_elem(current->left, key, compare);
        } else if (compare(current->key, key) < 0) {
            return bst_lookUpValue_elem(current->right, key, compare);
        }
    }
    printf("No such key");
    return NULL;
}

void* bst_lookUpValue(struct BST* tree, char* key,bst_compare_t compare){
    return bst_lookUpValue_elem(tree->root,key,compare);
}

int stringcmp(char* s1, char* s2){
    return strcmp(s1,s2);
}



void printBST_node(BST_node* node){
    if(node == NULL){
        return;
    }
    printBST_node(node->left);
    printBST_node(node->right);
    printf("key = %s, value = %u\n", node->key, (u32) node->value);
}

void printBST(struct BST* tree){
    if(tree->root ==NULL){
        return;
    }
    printBST_node(tree->root);

}
/*
int main(){
    struct BST * tree =getNewinitTree((void*) stringcmp);
    insertElem(tree,"hi",1,stringcmp);
    insertElem(tree,"yo",2,stringcmp);
    insertElem(tree, "ko",5,stringcmp);
    printBST(tree);
    printf("%d",(u32) bst_lookUpValue(tree,"yo",stringcmp));
}



*/



