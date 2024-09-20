#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bst.h"


Tree_Node* tree2_insert(Tree_Node* root, char data){
    if(root == NULL) {
        root = malloc(sizeof(Tree_Node));
        root -> data = data;
        root -> lower = NULL;
        root -> higher = NULL;
    }
    else if(data < root -> data) {
        root -> lower = tree2_insert(root -> lower, data);
    }
    else if(root -> data <= data) {
        root -> higher = tree2_insert(root -> higher, data);
    }
    return root;
}


Tree_Node* create_bst(char data[]){
    Tree_Node* root = NULL;
    for(int i = 0; i < strlen(data); i++) {
        root = tree2_insert(root, data[i]);
    }
    return root;
}

Tree_Node* tree_search(Tree_Node* root, char data){
    if(root == NULL) {
        return NULL;
    }
    else if(data < root -> data) {
        return tree_search(root -> lower, data);
    }
    else if(root -> data < data) {
        return tree_search(root -> higher, data);
    }
    else {
        return root;
    }
}

void tree_print_sorted(Tree_Node* root){
    if(root != NULL) {
        tree_print_sorted(root -> lower);
        printf("%c", root -> data);
        tree_print_sorted(root -> higher);
    }
}

void tree_delete(Tree_Node* root){
    if(root == NULL) {
        return;
    }
    tree_delete(root -> lower);
    tree_delete(root -> higher);
    free(root);
}

