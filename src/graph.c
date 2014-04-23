#include <stdlib.h>
#include <stdio.h>
#include "graph.h"

Node* create_node(){
    Node* node = malloc(sizeof(Node));
    node->name = -1;
    node->x = 0;
    node->y = 0;
    node->neighbors = NULL;
    node->neighbors_length = 0;
    node->neighbors_max_length = 0;
    node->has_received_signal = 0;
    node->state = 0;
}

void add_neighbor(Node* node, Node* neighbor){
    if(node->neighbors_length == node->neighbors_max_length){
        if(node->neighbors_max_length == 0){
            node->neighbors_max_length = 8;
        }else{
            node->neighbors_max_length *= 2;
        }
        if((node->neighbors = realloc(node->neighbors,
                sizeof(Node*) * node->neighbors_max_length)) == NULL) {
            printf("Ran out of memory when increasing neighbor list sizes\n");
            exit(1);     
        }
    }
    node->neighbors[node->neighbors_length++] = neighbor;
}

void read_graph(const char* filename, Node*** nodes, int* nodes_length){
    FILE *fp; 
    if((fp = fopen(filename, "r")) == NULL){
        printf("File not found\n");
        exit(1);
    }

    int number_of_vertices;
    int number_of_edges;

    fscanf(fp, "%d %d", &number_of_vertices, &number_of_edges);

    *nodes_length = number_of_vertices;
    *nodes = malloc(sizeof(Node*) * number_of_vertices);

    for(int i=0;i<number_of_vertices;i++){
        (*nodes)[i] = create_node();
        fscanf(fp, "%d %lf %lf",
                &((*nodes)[i]->name),
                &((*nodes)[i]->x),
                &((*nodes)[i]->y));
    }

    for(int i=0;i<number_of_edges;i++){
        int a, b;
        fscanf(fp, "%d %d", &a, &b);
        add_neighbor((*nodes)[b], (*nodes)[a]);
        add_neighbor((*nodes)[a], (*nodes)[b]);

    }
}

void destroy_graph(Node ** nodes, int length){
    for(int i=0;i<length;i++){
        free(nodes[i]->neighbors);
        free(nodes[i]);
    }
    free(nodes);
}

void print_graph(Node** nodes, int length){
    for(int i=0;i<length;i++){
        print_node(nodes[i]);
    }
    printf("\n");
}

void print_node(Node* node){
    printf("%d ", node->name);
}
