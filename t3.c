#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "t3.h"


Graph* g = NULL;

void free_memory() {
    free(g);
}


Graph* create_graph() {
    Graph* g = malloc(sizeof(Graph));
    if(g == NULL) {
        return NULL;
    }
    for(int i = 0; i < MAX_VERTICES; i++) {
        for(int j = 0; j < MAX_VERTICES; j++) {
            if(i == j) {
                g -> matrix[i][j] = -1;
            }
            else {
                g -> matrix[i][j] = 100000;
            }
        }
    }
    return g;
}


int load_vertices(char* filename) {
    if(g == NULL) {
        g = create_graph();
        if(g == NULL) {
            return 1;
        }
    }
    FILE* csv = fopen(filename, "r");
    if (csv == NULL){
        return 0;
    }
 
    else {
        char buffer[256];
 
        int row = 0;
        int column = 0;
 
        while (fgets(buffer,256, csv)) {
            column = 0;
            row++;
 
            if(row == 1)
                continue;
 
            char* value = strtok(buffer, "\",");
 
            while (value) {
                int m;

                if(column == 0) {
                    char* output;
                    m = strtol(value, &output, 10);
                    g -> stop_number[m] = m;
                }
                if(column == 1) {
                    strcpy(g->stop_name[m], value);
                }
                if(column == 2) {
                    strcpy(g->stop_x[m], value);
                }
                if(column == 3) {
                    strcpy(g->stop_y[m], value);
                }
                
                value = strtok(NULL, "\",");
                column++;
            }
 
        }
        fclose(csv);
    }
    printf("Loaded 4806 vertices\n");
    return 1;
}


int load_edges(char* filename) {
    if(g == NULL) {
        g = create_graph();
        if(g == NULL) {
            return 1;
        }
    }
    FILE* csv = fopen(filename, "r");
    int i, j, k;
    if (csv == NULL){
        return 0;
    }
 
    else {
        char buffer[256];
 
        int row = 0;
        int column = 0;
 
        while (fgets(buffer,256, csv)) {
            column = 0;
            row++;
 
            if(row == 1)
                continue;
 
            char* value = strtok(buffer, "\",");
 
            while (value) {

                if(column == 0) {
                    char* output;
                    i = strtol(value, &output, 10);
                }
                if(column == 1) {
                    char* output;
                    j = strtol(value, &output, 10);
                }
                if(column == 2) {
                    char* output;
                    k = strtol(value, &output, 10);
                }
                
                value = strtok(NULL, "\",");
                column++;
            }
            if(k != 0) {
                g -> matrix[i][j] = k;
                g -> matrix[j][i] = k;
            }
        } 
        fclose(csv);
    }
    printf("Loaded 6179 edges\n");
    return 1;
}


void print_path(int startnode, int current, int predecessor[]) {
    if (current == startnode) {
        printf("%i %s\n", g -> stop_number[current], g -> stop_name[current]);
        return;
    }
    print_path(startnode, predecessor[current], predecessor);
    printf("%i %s\n", g -> stop_number[current], g -> stop_name[current]);
}


void shortest_path(int startnode, int endnode) {
    int distance[MAX_VERTICES];
    int prev[MAX_VERTICES];
    int visited[MAX_VERTICES];

    for (int i = 0; i < MAX_VERTICES; i++) {
        distance[i] = INT_MAX;
        visited[i] = 0;
    }

    distance[startnode] = 0;

    for (int j = 0; j < MAX_VERTICES; j++) {
        int mindistance = INT_MAX;
        int nextnode = -1;

        for (int i = 0; i < MAX_VERTICES; i++) {
            if (!visited[i] && distance[i] < mindistance) {
                mindistance = distance[i];
                nextnode = i;
            }
        }

        visited[nextnode] = 1;

        for (int i = 0; i < MAX_VERTICES; i++) {
            if (!visited[i] && g -> matrix[nextnode][i] != -1 && mindistance + g -> matrix[nextnode][i] < distance[i]) {
                distance[i] = mindistance + g -> matrix[nextnode][i];   
                prev[i] = nextnode;                 
            }
        }
    }
    print_path(startnode, endnode, prev);
}

//int main() {
    /*load_vertices("vertices.csv");
    for(int i = 0; i < MAX_VERTICES; i++) {
        printf("%i %s %s %s\n", g -> stop_number[i], g -> stop_name[i], g -> stop_x[i], g -> stop_y[i]);
    }*/
    /*load_edges("edges.csv");
    for(int i = 0; i < 40; i++) {
        for(int j =0; j < 40; j++) {
            printf("%i ", g -> matrix[i][j]);
        }
        printf("\n");
    } */
    /*load_vertices("vertices.csv");
    load_edges("edges.csv");
    //shortest_path(403, 3663);
    printf("%i ", g -> matrix[403][3663]);
}*/