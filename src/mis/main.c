#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "graph.h"
#include "mis.h"


int main(int argc, char**argv){

    if(argc == 1) {
        printf("Minimal Independant Set Solver 3000™\n");
        printf("Usage: mis filename [options]\n");
        return -1;
    }

    srand(time(NULL));

    Node** nodes = NULL;
    int nodes_length = 0;
    read_graph(argv[1], &nodes, &nodes_length);

    int number_of_leaders = mis(nodes, nodes_length);

    puts(argv[1]);
    for(int i = nodes_length - number_of_leaders; i < nodes_length; i++){
        printf("%d 1\n", nodes[i]->name);
    }

    destroy_graph(nodes, nodes_length);
    return 0;
}
