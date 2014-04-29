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

int mis(Node** nodes, int nodes_length, int M, int* active_nodes){

    /* find maximum degree of graph */
    int maximum_degree = 0;
    for(int i=0;i<nodes_length;i++){
        if(nodes[i]->neighbors_length > maximum_degree){
            maximum_degree = nodes[i]->neighbors_length;
        }
    }
    
    double p = 1. / maximum_degree;

    int number_of_active_nodes = nodes_length;
    int number_of_leaders = 0;
    int number_of_non_leaders = 0;

    int m_log2_n = M * log((double)nodes_length) / log(2.);

    while(p < 1) {

        for(int i=0;i<m_log2_n;i++){

            /* round 1 */
            for(int j = number_of_non_leaders;
                    j < number_of_non_leaders + number_of_active_nodes;
                    j++){
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
            }

            /* reset signals */
            for(int j = number_of_non_leaders;
                    j < number_of_non_leaders + number_of_active_nodes;
                    j++){
                nodes[j]->has_received_signal = 0;
            }

            /* round 2 */
            for(int j = number_of_non_leaders;
                    j < number_of_non_leaders + number_of_active_nodes;
                    j++){
                Node* node = nodes[j];
                if(node->state == 1){
                    for(int k=0;k<node->neighbors_length;k++){
                        Node* neighbor = node->neighbors[k];
                        neighbor->has_received_signal = 1;
                    }
                    swap(nodes, j--, nodes_length - number_of_leaders++ - 1);
                    number_of_active_nodes--;
                }
            }
            for(int j = number_of_non_leaders;
                    j < number_of_non_leaders + number_of_active_nodes;
                    j++){
                Node* node = nodes[j];
                if(node->has_received_signal){
                    swap(nodes, j, number_of_non_leaders++);
                    number_of_active_nodes--;
                }
            }
        }
        p *= 2;
    }

    return number_of_leaders;
}

int mis_verify(Node** nodes, int nodes_length, int* adjacent_leader_pairs,
               int* leaderless_nodes){
    *adjacent_leader_pairs = 0;
    *leaderless_nodes = 0;
    for(int i=0;i<nodes_length;i++){
        Node* node = nodes[i];
        int leaderless = 1;
        if(node->state == 1){
            leaderless = 0;
        }
        for(int j=0;j<node->neighbors_length;j++){
            Node* neighbor = node->neighbors[j];
            if(neighbor->state == 1){
                leaderless = 0;
                if(node->state == 1){
                    (*adjacent_leader_pairs)++;
                }
            }
        }
        if(leaderless){
            (*leaderless_nodes)++;
        }
    }

    *adjacent_leader_pairs /= 2;

    return (*adjacent_leader_pairs) + (*leaderless_nodes);
}
