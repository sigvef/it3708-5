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
    return p < (double) rand() / RAND_MAX;
}

int mis(Node** nodes, int nodes_length){

    /* find maximum degree of graph */
    int maximum_degree = 0;
    for(int i=0;i<nodes_length;i++){
        if(nodes[i]->neighbors_length > maximum_degree){
            maximum_degree = nodes[i]->neighbors_length;
        }
    }

    double p = 1 / maximum_degree;

    int number_of_active_nodes = nodes_length;
    int number_of_leaders = 0;
    int number_of_non_leaders = 0;

    int M = 34;
    int m_log2_n = 34 * log((double)nodes_length) / log(2.);

    for(int i=0;i<m_log2_n;i++){

        if(p > 1) {
            return number_of_leaders;
        }

        /* round 1 */
        for(int j=0;j<number_of_active_nodes;j++){
            Node* node = nodes[j];

            if(random(p)){
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

        /* round 2 */
        for(int j=0;j<number_of_active_nodes;j++){
            Node* node = nodes[j];
            if(node->state == 1){
                for(int k=0;k<node->neighbors_length;k++){
                    Node* neighbor = node->neighbors[k];
                    neighbor->has_received_signal = 1;
                }
                printf("found a leader: %d\n", node->name);
                swap(nodes, j--, nodes_length - number_of_leaders++ - 1);
                number_of_active_nodes--;
            }else{
                if(node->has_received_signal){
                    swap(nodes, j--, --number_of_active_nodes);
                }
            }
        }
        p *= 2;
    }

    return number_of_leaders;
}
