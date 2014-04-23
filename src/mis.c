#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "mis.h"
#include "graph.h"

void swap(Node** array, int i, int j){
    Node* temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

bool random(double p){
    return p > (double) rand() / RAND_MAX;
}

int mis(Node** nodes, int nodes_length){

    printf("starting mis!\n");

    /* find maximum degree of graph */
    int maximum_degree = 0;
    for(int i=0;i<nodes_length;i++){
        if(nodes[i]->neighbors_length > maximum_degree){
            maximum_degree = nodes[i]->neighbors_length;
        }
    }
    
    printf("maximum degree: %d\n", maximum_degree);

    double p = 1. / maximum_degree;
    printf("p: %f\n", p);

    int number_of_active_nodes = nodes_length;
    int number_of_leaders = 0;
    int number_of_non_leaders = 0;

    int M = 34;
    int m_log2_n = 34 * log((double)nodes_length) / log(2.);
    printf("m_log2_n: %i\n", m_log2_n);

    while(p < 1) {

        printf("acnodes: %i \n", number_of_active_nodes);

        for(int i=0;i<m_log2_n;i++){

            //printf("\n\n==== started mlog2n %i ====\n\n", i);

            /* round 1 */
            //printf("-- round 1! --\n");
            for(int j = number_of_non_leaders;
                    j < number_of_non_leaders + number_of_active_nodes;
                    j++){
                Node* node = nodes[j];

                if(random(p)){
                    printf("triggered! Node: %i\n", node->name);
                    for(int k=0;k<node->neighbors_length;k++){
                        Node* neighbor = node->neighbors[k];
                        neighbor->state = 0;
                        neighbor->has_received_signal = 1;
                    }
                    if(!node->has_received_signal){
                        node->state = 1;
                    }
                }
                node->has_received_signal = 0;
            }

            /* reset signals */
            int reset_needed = 0;
            for(int j = number_of_non_leaders;
                    j < number_of_non_leaders + number_of_active_nodes;
                    j++){
                if(nodes[j]->has_received_signal){
                    reset_needed = 1; 
                }
                nodes[j]->has_received_signal = 0;
            }
            if(reset_needed){
                printf("reset\n");
            }

            /* round 2 */
            //printf("\n-- round 2! --\n");
            for(int j = number_of_non_leaders;
                    j < number_of_non_leaders + number_of_active_nodes;
                    j++){
                Node* node = nodes[j];
                if(node->state == 1){
                    for(int k=0;k<node->neighbors_length;k++){
                        Node* neighbor = node->neighbors[k];
                        neighbor->has_received_signal = 1;
                    }
                    printf("[%i (%i) %i] made node %i a LEADER\n", number_of_non_leaders, j, number_of_leaders, node->name);
                    printf("before: ");
                    print_graph(nodes, nodes_length);
                    swap(nodes, j--, nodes_length - number_of_leaders++ - 1);
                    number_of_active_nodes--;
                    printf("after:  ");
                    print_graph(nodes, nodes_length);
                    printf("\n");
                }
            }
            for(int j = number_of_non_leaders;
                    j < number_of_non_leaders + number_of_active_nodes;
                    j++){
                Node* node = nodes[j];
                if(node->has_received_signal){
                    printf("[%i (%i) %i] made node %i a non-leader\n", number_of_non_leaders, j, number_of_leaders, node->name);
                    printf("before: ");
                    print_graph(nodes, nodes_length);
                    swap(nodes, j, number_of_non_leaders++);
                    number_of_active_nodes--;
                    printf("after:  ");
                    print_graph(nodes, nodes_length);
                    printf("\n");
                }
            }
        }
        p *= 2;
    }

    return number_of_leaders;
}
