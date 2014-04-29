#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "graph.h"
#include "vc.h"


int main(int argc, char**argv){

    if(argc != 3 && argc != 4 && argc != 5) {
        printf("Vertex Coloring Solver 3000™\n");
        printf("Usage: vc filename n_colors [probability dampener] [--single]\n");
        printf("      (all arguments are positional)\n");
        return -1;
    }

    srand(time(NULL));

    int violations = 0;
    int uncolored = 0;
    int same_color_neighbor_pairs = 0;
    Node** nodes = NULL;
    int nodes_length = 0;
    read_graph(argv[1], &nodes, &nodes_length, atoi(argv[2]));

    for(int _=0;_<(argc == 5 ? 1 : 1000);_++){
        vc(nodes, nodes_length, argc >= 4 ? (double) atoi(argv[3]) : 1000.);
        violations = vc_verify(nodes, nodes_length, &uncolored,
                               &same_color_neighbor_pairs);
        if(violations == 0){
            break;
        }
    }

    puts(argv[1]);
    for(int i=0;i<nodes_length;i++){
        printf("%d %d\n", nodes[i]->name, nodes[i]->selected_color);
    }

    fprintf(stderr, "Uncolored nodes: %d\n", uncolored);
    fprintf(stderr, "Same color neighbor pairs: %d\n", same_color_neighbor_pairs);
    fprintf(stderr, "Total violations: %d\n", violations);
    fprintf(stderr, violations ? "BAD SOLUTION\n" : "Good Solution!\n");

    destroy_graph(nodes, nodes_length);

    return 0;
}
