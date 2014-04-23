#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#include "mis.h"


int main(){

    Node** nodes = NULL;
    int nodes_length = 0;
    printf("going to read graph\n");
    read_graph("res/graph-color-1.txt", &nodes, &nodes_length);
    printf("read graph finished\n");

    printf("going to mis\n");
    mis(nodes, nodes_length);
    printf("done with mis\n");

    destroy_graph(nodes, nodes_length);
    return 0;
}
