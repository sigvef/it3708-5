#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "graph.h"
#include "mis.h"


int main(){

    srand(time(NULL));

    Node** nodes = NULL;
    int nodes_length = 0;
    printf("going to read graph\n");
    read_graph("res/two-leaders.txt", &nodes, &nodes_length);
    printf("read graph finished\n");

    print_graph(nodes, nodes_length);

    printf("going to mis\n");
    int number_of_leaders = mis(nodes, nodes_length);
    printf("done with mis\n");

    printf("leaders: ");
    for(int i = nodes_length - number_of_leaders; i < nodes_length; i++){
        printf("%d ", nodes[i]->name);
    }
    printf("\n");

    destroy_graph(nodes, nodes_length);
    return 0;
}
