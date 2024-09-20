#ifndef T1_H_
#define T1_H_

#define MAX 12

typedef struct Node{
    int value;
    struct Node* next;
} Node;

typedef struct Graph{
    Node** adj;
    int* visited;
} Graph;

typedef struct Queue {
  int items[MAX];
  int front;
  int rear;
} Queue;

Graph* create_graph(int num_nodes); // creates a graph with num_nodes nodes, assuming nodes are stored in alphabetical order (A, B, C..)
void add_edge(Graph *g, int from, int to); // adds a directed edge
void bfs(Graph* g, int origin); //implements breath first search and prints the results
void dfs(Graph* g, int origin); //implements depth first search and prints the results
void delete_graph(Graph* g);

#endif