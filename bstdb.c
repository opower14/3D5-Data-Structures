#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bstdb.h"

#define LIST_SIZE (2^17)


typedef struct Tree_Node{
    char *data;
	int doc_id;
	int word_count;
    struct Tree_Node *lower;
    struct Tree_Node *higher;
} Tree_Node;


Tree_Node* root;
Tree_Node* head;
int numerator = 1;
int denominator = 2;


/*Tree_Node* tree2_insert(Tree_Node* root, char *data, int word_count, int doc_id){
    if(root == NULL) {
        root = malloc(sizeof(Tree_Node));
        root -> data = strdup(data);
		root -> word_count = word_count;
		root -> doc_id = doc_id;
        root -> lower = NULL;
        root -> higher = NULL;
    }
    else if(doc_id < root -> doc_id) {
        root -> lower = tree2_insert(root -> lower, data, word_count, doc_id);
    }
    else if(doc_id > root -> doc_id) {
        root -> higher = tree2_insert(root -> higher, data, word_count, doc_id);
    }
    return root;
}*/

void tree_delete(Tree_Node* root){
    if(root == NULL) {
        return;
    }
    tree_delete(root -> lower);
    tree_delete(root -> higher);
	free(root -> data);
    free(root);
}


Tree_Node* tree2_insert(Tree_Node* root, char *data, int word_count, int doc_id){
	if(root == NULL) {
		root = malloc(sizeof(Tree_Node));
		if(root) {
			root -> word_count = word_count;
		    root -> doc_id = doc_id;
	    	root -> lower = NULL;
	    	root -> higher = NULL;
			root -> data = calloc((strlen(data) + 1), sizeof(char));
			if(root -> data) {
				strcpy(root -> data, data);
			}
			else {
				tree_delete(root);
				root = NULL;
				return NULL;
			}
		}
		return root;
	}
	else if(doc_id < root -> doc_id) {
		return tree2_insert(root -> lower, data, word_count, doc_id);
	}
	else if(doc_id > root -> doc_id) {
		return tree2_insert(root -> higher, data, word_count, doc_id);
	}
	return root;
}


Tree_Node* tree_search(Tree_Node* root, int doc_id){
    if(root == NULL || root -> doc_id == doc_id) {
		return root;
	}
	else if (doc_id < root -> doc_id) {
		return tree_search(root -> lower, doc_id);
	}
	else {
		return tree_search(root -> higher, doc_id);
	}
}


int Doc_ID(void) {
	int doc_id = (LIST_SIZE * (numerator / denominator));
	if(numerator == (denominator / 2)) {
		denominator = (denominator * 2);
		numerator = 1;
	}
	else {
		numerator = numerator + 2;
	}
	return doc_id;
}


int bstdb_init ( void ) {
    head = NULL;
	root = NULL;

	return 1;
}


int bstdb_add ( char *name, int word_count, char *author ) {
	int doc_id = Doc_ID();
	root = head;
	root = tree2_insert(root, name, word_count, doc_id);
	if(head == NULL) {
		head = root;
	}
	if(head -> lower == NULL && head -> doc_id > doc_id) {
		head -> lower = root;
	}
	if(head -> higher == NULL && head -> doc_id < doc_id) {
		head -> higher = root;
	}
	if(root == NULL) {
		return -1;
	}
	return root -> doc_id;
}


int bstdb_get_word_count(int doc_id) {
	root = head;
	root = tree_search(root, doc_id);
	if(root == NULL || root -> doc_id != doc_id) {
		return -1;
	}
	return root -> word_count;
}


char* bstdb_get_name(int doc_id) {
	root = head;
	root = tree_search(root, doc_id);
	if(root == NULL || root -> doc_id != doc_id) {
		return NULL;
	}
	return root -> data;
}


void bstdb_stat ( void ) {
	// Use this function to show off! It will be called once after the 
	// profiler ends. The profiler checks for execution time and simple errors,
	// but you should use this function to demonstrate your own innovation.
	//
	// Suggestions for things you might want to demonstrate are given below,
	// but in general what you choose to show here is up to you. This function
	// counts for marks so make sure it does something interesting or useful.
	//
	//  + Check if your tree is balanced and print the result
	//
	//  + Does the number of nodes in the tree match the number you expect
	//    based on the number of insertions you performed?
	//
	//  + How many nodes on average did you need to traverse in order to find
	//    a search result? 
	//
	//  + Can you prove that there are no accidental duplicate document IDs
	//    in the tree?
}


void bstdb_quit ( void ) {
	root = head;
	tree_delete(root);
}
