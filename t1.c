#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "t1.h"


int total_nodes = 0;
int b = 0;


void delete_graph(Graph* graph) {
    for (int i = 0; i < total_nodes; i++) {
        Node* current = graph->adj[i];
        while (current) {
            Node* next = current->next;
            free(current);
            current = next;
        }
    }
    free(graph->visited);
    free(graph->adj);
    free(graph);
}


Graph* create_graph(int num_nodes) {
    total_nodes = num_nodes;
    Graph* g = malloc(sizeof(Graph));
    g -> adj = malloc(num_nodes * sizeof(Node*));
    g -> visited = malloc(num_nodes * sizeof(int));

    for(int i = 0; i < num_nodes; i++) {
        g -> adj[i] = NULL;
    }
    return g;
} 


Node* create_node(int value) {
    Node* node = malloc(sizeof(Node));
    node -> value = value;
    node -> next = NULL;
    return node;
}


void add_edge(Graph *g, int from, int to) {
    Node* node = create_node(to);
    node -> next = g -> adj[from];
    g -> adj[from] = node;
}


void bfs(Graph* g, int origin) {
    for(int i = 0; i < total_nodes; i++) {
        g -> visited[i] = 0;
    }
    Queue* q = malloc(sizeof(Queue));
    g -> visited[origin] = 1;
    q -> front = 0;
    q -> rear = 0;  
    q -> items[q -> rear] = origin;
    printf("BFS ");

    while(q -> front <= q -> rear) {
        int value = q -> items[q -> front];
        char val = value + 'A';
        printf(" %c ", val);
        Node* temp = g -> adj[value];

        while(temp) {
            int temp_value = temp -> value;
            if (g -> visited[temp_value] == 0) {
                g -> visited[temp_value] = 1;
                q -> rear++;
                q -> items[q -> rear] = temp_value;
            }
            temp = temp -> next;
        }
        q -> front++;
    }
    printf("\n");
    free(q);
}


void DFS(Graph* g, int origin) {
    Node* temp = g -> adj[origin];
    g -> visited[origin] = 1;
    char val = origin + 'A';
    printf(" %c ", val);

    while(temp) {
        int value = temp -> value;
        if (g -> visited[value] == 0) {
            DFS(g, value);
        }
        temp = temp -> next;
    }
}


void dfs(Graph* g, int origin) {
    for(int i = 0; i < total_nodes; i++) {
        g -> visited[i] = 0;
    }
    Node* temp = g -> adj[origin];
    g -> visited[origin] = 1;
    char val = origin + 'A';
    printf("DFS:");
    printf(" %c ", val);

    while(temp) {
        int value = temp -> value;
        if (g -> visited[value] == 0) {
            DFS(g, value);
        }
        temp = temp -> next;
    }
    if(temp == NULL) {
        printf("\n");
    }
}



