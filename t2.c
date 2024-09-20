#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "t2.h"


int total_nodes = 0;


void delete_graph(Graph* graph) {
    free(graph);
}


Graph* create_graph(int num_nodes) {
    total_nodes = num_nodes;
    Graph* g = malloc(sizeof(Graph));

    for(int i = 0; i < num_nodes; i++) {
        for(int j = 0; j < num_nodes; j++) {
            if(i == j) {
                g -> matrix[i][j] = -1;
            }
            else {
                g -> matrix[i][j] = 0;
            }
        }
    }
    return g;
}


void add_edge(Graph *g, int from, int to, int weight) {
    g -> matrix[from][to] = weight;
    g -> matrix[to][from] = weight;
}


void dijkstra(Graph* g, int origin) {
    int distance[total_nodes];
    int distance2[total_nodes];
    int visited[total_nodes];

    for (int i = 0; i < total_nodes; i++) {
        distance[i] = INT_MAX;
        visited[i] = 0;
    }

    distance[origin] = 0;
    distance2[origin] = 0;

    for (int j = 0; j < total_nodes; j++) {
        int mindistance = INT_MAX;
        int nextnode = -1;

        for (int i = 0; i < total_nodes; i++) {
            if (!visited[i] && distance[i] < mindistance) {
                mindistance = distance[i];
                nextnode = i;
            }
        }

        visited[nextnode] = 1;

        for (int i = 0; i < total_nodes; i++) {
            if (!visited[i] && g -> matrix[nextnode][i] && mindistance + g -> matrix[nextnode][i] < distance[i]) {
                distance[i] = mindistance + g -> matrix[nextnode][i];
                distance2[i] = distance[i];
            }
        }
    }

    for(int i = 0; i < total_nodes; i++) {
        char letter;
        int temp = INT_MAX;
        int position;
        for(int j = 0; j < total_nodes; j++) {
            if(temp > distance2[j]) {
                letter = j + 'A';
                temp = distance2[j];
                position = j;
            }
        }
        distance2[position] = INT_MAX;
        printf("%c ", letter);
    }
    printf("\n");

    for (int i = 0; i < total_nodes; i++) {
        char val = i + 'A';
        char val2 = origin + 'A';
        printf("The length of the shortest path between %c and %c is %d\n", val2, val, distance[i]);
    }
}




// converts an upper case character (A-Z) to a numerical value (between 0 and 25) 
static int char2val ( char c ) {
	if ( c < 'A' || c > 'Z' ) {
		return -1;
	}

	return c-'A';
}

int main(){
    int num_nodes = 7;
    Graph *graph = create_graph(num_nodes);
   
    add_edge(graph, char2val('A'), char2val('B'), 1);
    add_edge(graph, char2val('A'), char2val('C'), 3);
    add_edge(graph, char2val('A'), char2val('F'), 10);
    add_edge(graph, char2val('B'), char2val('G'), 2);
    add_edge(graph, char2val('B'), char2val('D'), 7);
    add_edge(graph, char2val('B'), char2val('E'), 5);
    add_edge(graph, char2val('B'), char2val('C'), 1);
    add_edge(graph, char2val('C'), char2val('D'), 9);
    add_edge(graph, char2val('C'), char2val('E'), 3);
    add_edge(graph, char2val('D'), char2val('G'), 12);
    add_edge(graph, char2val('D'), char2val('F'), 1);
    add_edge(graph, char2val('D'), char2val('E'), 2);
    add_edge(graph, char2val('E'), char2val('F'), 2);

    dijkstra(graph, char2val('C'));
    
    delete_graph(graph);

}