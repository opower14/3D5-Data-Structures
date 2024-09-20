#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


#define MAX_STRING_SIZE 20 
#define ARRAY_SIZE 59  


typedef struct Element Element;
struct Element{
    char word[MAX_STRING_SIZE];
    int key;
    int counter;
};

Element* hashTable[ARRAY_SIZE] = {NULL};
int collisions = 0;
int num_terms = 0;

int hash_function(char* s){
    int hash = 0;
    while(*s){
       hash = (hash + *s - 'A') %ARRAY_SIZE;
        s++;
    }
    return hash;
}
Element* createNewElement(char* name){
    struct Element* data = (struct Element*)malloc(sizeof(struct Element));
    data -> key = hash_function(name);
    strcpy(data -> word, name);

	return data;
}


void addOrIncrement(char* name){
   struct Element* data = createNewElement(name);
   int hashIndex = data -> key;
   int i = 0;
   num_terms++;
   int j = 0;
   int k = 0;
   while(hashTable[hashIndex] != NULL) {
    if(strcmp(hashTable[hashIndex] -> word, name) == 0) {
        num_terms--;
        j = 1;
        collisions = collisions - k;
        hashTable[hashIndex] -> counter = hashTable[hashIndex] -> counter + 1;
        break;
    }
    i++;
    collisions++;
    hashIndex = hashIndex^i % ARRAY_SIZE;
    k++;
    if(hashIndex > ARRAY_SIZE) {
        hashIndex = hashIndex % ARRAY_SIZE;
    }
   }
   if(j == 0) {
     data -> counter = 1;
     hashTable[hashIndex] = data;
   }
}


void printNumberOfOccurences(char* name){
    int i = 0;
    int j = 0;
    for (i = 0; i < ARRAY_SIZE; i++) {
    if(hashTable[i] -> word == NULL) {

    }
    else {
    if(strcmp(name, hashTable[i] -> word) == 0) {
        printf("%s - %d \n>>> ", name, hashTable[i] -> counter);
        j = 1;
    }
    }
    }
    if (j == 0) {
        printf("%s - 0 \n>>> ", name);
    }
    scanf ("%[^\n]%*c", name);
}


void next_token ( char *buf, FILE *f, int string_max ) {
	buf[0] = fgetc(f);
	while ( !isalnum(buf[0]) && !feof(f) ) { 
        buf[0] = fgetc(f); 
        }

	int i=1;
	for (;;) {
		buf[i] = fgetc(f); 
		if( !isalnum(buf[i]) ) { 
            if(buf[i]!=' '){ 
                break;
            }
        } 
		if( feof(f) ) { 
            break; 
            }
		if( i < (string_max-1) ) { 
            ++i; 
            }
	}
	buf[i] = '\0';
}


int load_file ( char *fname ) {
	FILE *f;
	char buf[MAX_STRING_SIZE];

	f = fopen(fname, "r");
	if (!f) { 
		printf("Unable to open %s\n", fname);
		return 0; 
	}
	
	while ( !feof(f) ) {
		next_token(buf, f, MAX_STRING_SIZE);
		addOrIncrement(buf);
	}
    
    printf("File %s loaded\n", fname);
    
    float load = (num_terms/59.0);
    printf(" Capacity: %i\n Num Terms: %i\n Collisions: %i\n Load: %f\n", ARRAY_SIZE, num_terms, collisions, load);
	fclose(f);

	return 1;
}


int main ( int argc, char *argv[] ) {
    char name[MAX_STRING_SIZE];
    load_file("names.csv");
    printf("Enter term to get frequency or type \"quit\" to escape\n>>> ");
    scanf ("%[^\n]%*c", name);
    while(strcmp(name, "quit") != 0) {
        printNumberOfOccurences(name);
    }
    
    
    
    return 0;
}
