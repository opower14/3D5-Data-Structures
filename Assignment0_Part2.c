#include <stdio.h>
#include <string.h>
 
// Driver Code
int main()
{
    FILE* csv = fopen("pokemon.csv", "r");
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
    
                if (column == 0) {
               printf("\n");
                }

                if (column == 1) {
                   printf("\n");
                }

                if (column == 2) {
                 printf("\n");
                }

                if (column == 3) {
                 printf("\n");
                }
                
                if (column == 4) {
                 printf("\n");
                }

                if (column == 5) {
               printf("\n");
                }

                if (column == 6) {
                   printf("\n");
                }

                if (column == 7) {
               printf("\n");
                }
 
                if (column == 8) {
                   printf("\n");
                }

                if (column == 9) {
                 printf("\n");
                }

                if (column == 10) {
               printf("\n");
                }

                if (column == 11) {
                   printf("\n");
                }
 
                if (column == 12) {
                 printf("\n");
                }

                if (column == 13) {
               printf("\n");
                }
           
                if (column > 13) {
               printf(" ");
                }
                
 
                printf("%s", value);
                value = strtok(NULL, ", ");
                column++;
            }
 
            printf("\n");
        }
 
        fclose(csv);
    }
    return 0;
}