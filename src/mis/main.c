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

    int active_nodes = 0;
    int number_of_leaders = mis(nodes, nodes_length, &active_nodes);

    int adjacent_leader_pairs = 0;
    int leaderless_nodes = 0;
    int violations = mis_verify(nodes, nodes_length, &adjacent_leader_pairs,
                                &leaderless_nodes);
    violations += active_nodes;

    puts(argv[1]);
    for(int i = nodes_length - number_of_leaders; i < nodes_length; i++){
        printf("%d 1\n", nodes[i]->name);
    }

    fprintf(stderr, "Adjacent leader pairs: %d\n", adjacent_leader_pairs);
    fprintf(stderr, "Leaderless nodes: %d\n", leaderless_nodes);
    fprintf(stderr, "Still-active nodes: %d\n", active_nodes);
    fprintf(stderr, "Total violations: %d\n", violations);
    fprintf(stderr, violations ? "BAD SOLUTION\n" : "Good Solution!\n");

    destroy_graph(nodes, nodes_length);

    return 0;
}
