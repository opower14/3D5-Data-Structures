#ifndef T3_H_
#define T3_H_

#define MAX_VERTICES 7668

typedef struct Graph{
    int matrix[MAX_VERTICES][MAX_VERTICES];
    int stop_number[MAX_VERTICES];
    char stop_name[MAX_VERTICES][30];
    char stop_x[MAX_VERTICES][15];
    char stop_y[MAX_VERTICES][15];
} Graph;

int load_edges ( char *fname ); //loads the edges from the CSV file of name fname
int load_vertices ( char *fname );  //loads the vertices from the CSV file of name fname
void shortest_path(int startNode, int endNode); // prints the shortest path between startNode and endNode, if there is any
void free_memory ( void ) ; // frees any memory that was used

#endif