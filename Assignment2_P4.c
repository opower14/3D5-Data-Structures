#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


#define MAX_STRING_SIZE 20 
#define ARRAY_SIZE 99991


int Load_surnames(char* filename) {

    FILE* csv = fopen(filename, "r");
    int c;
    if (csv == NULL){
        printf("Can't open file\n");
    }
 
    else {
        char buffer[256];
        char surname[ARRAY_SIZE][MAX_STRING_SIZE];
 
        int row = 0;
        int column = 0;
 
        while (fgets(buffer,256, csv)) {
            column = 0;
            row++;
 
            if (row == 1)
                continue;
 
            char* value = strtok(buffer, ", ");
 
            while (value) {

                if (column == 2) {
                 strcpy(surname[row], value);
                }
                value = strtok(NULL, "\",");
                column++;
            }
 
        }
 
        fclose(csv);
    }
    return 0;
}

int Lad_Total_file(char* filename) {
    FILE* csv = fopen(filename, "r");
    int c;
    if (csv == NULL){
        printf("Can't open file\n");
    }
 
    else {
        char buffer[256];
        char total_file[ARRAY_SIZE][256];
 
        int row = 0;
        int column = 0;
 
        while (fgets(buffer,256, csv)) {
            column = 0;
            row++;
 
            char* value = strtok(buffer, "\n");
 
            while (value) {

                strcpy(total_file[row], value);
                value = strtok(NULL, "\n");
                column++;
            }
 
        }
 
        fclose(csv);
    }
    return 0;
}


int main () {
    char surname[ARRAY_SIZE][256];
    char total_file[ARRAY_SIZE][256];
    FILE* csv = fopen("truncated.csv", "r");
    int c;
    if (csv == NULL){
        printf("Can't open file\n");
    }
 
    else {
        char buffer[256];
 
        int row = 0;
        int column = 0;
 
        while (fgets(buffer,256, csv)) {
            column = 0;
            row++;
 
            if (row == 1)
                continue;
 
            char* value = strtok(buffer, ", ");
 
            while (value) {

                if (column == 2) {
                 strcpy(surname[row], value);
                }
                value = strtok(NULL, "\",");
                column++;
            }
 
        }
 
        fclose(csv);
    }
    FILE* csv2 = fopen("truncated.csv", "r");
    if (csv2 == NULL){
        printf("Can't open file\n");
    }
 
    else {
        char buffer[256];
 
        int row = 0;
        int column = 0;
 
        while (fgets(buffer,256, csv2)) {
            column = 0;
            row++;
 
            char* value = strtok(buffer, "\n");
 
            while (value) {

                strcpy(total_file[row], value);
                value = strtok(NULL, "\n");
                column++;
            }
 
        }
 
        fclose(csv2);
    }
    int i = 0;
    int j = 0;
    char name[256];
    printf("Enter term to get frequency or type \"quit\" to escape\n>>> ");
    scanf ("%[^\n]%*c", name);
    while(strcmp(name, "quit") != 0) {
    for(i = 0; i < ARRAY_SIZE; i++) {
        if(strcmp(name, surname[i]) == 0) {
            j++;
            if(j > 1) {
                printf("%s\n>>>", total_file[i]);
        }
        }
        if(j == 1) {
        printf("%s\n", total_file[1]);
        printf("%s\n>>>", total_file[i]);
        j++;
        }
    }
    if(j == 0) {
        printf("%s not in table\n>>>", name);
    }
    j = 0;
    scanf ("%[^\n]%*c", name);
    }
}
 