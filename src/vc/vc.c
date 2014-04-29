#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "vc.h"
#include "graph.h"

void node_swap(Node** array, int i, int j){
    Node* temp = array[i];
    array[i] = array[j];
    array[i]->index = i;
    temp->index = j;
    array[j] = temp;
}

void int_swap(int* array, int i, int j){
    int temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

bool random(double p){
    return p > (double) rand() / RAND_MAX;
}

int randint(int low, int high){
    return low + (int)((double) rand() / (RAND_MAX - 1) * (high - low));
}

int vc(Node** nodes, int nodes_length, double probability_dampener){

    /* find maximum degree of graph */
    int maximum_degree = 0;
    for(int i=0;i<nodes_length;i++){
        Node* node = nodes[i];
        if(node->neighbors_length > maximum_degree){
            maximum_degree = node->neighbors_length;
        }
        /* reset some stuff as well */
        node->state = 0;
        node->signalled_colors_length = 0;
        node->available_colors_length = node->available_colors_max_length;
    }
    
    double p = 1. / maximum_degree / probability_dampener;

    int number_of_non_permanents = nodes_length;

    int M = 3400;
    int m_log2_n = M * log((double)nodes_length) / log(2.);

    while(p < 1) {

        for(int i=0;i<m_log2_n;i++){

            /* round 1: chance of tentative color selection */
            for(int j=0;j<number_of_non_permanents;j++){
                Node* node = nodes[j];

                if(node->available_colors_length == 0){
                    /* randomly undo a neighbor's color choice */
                    Node* neighbor = node->neighbors[
                        randint(0, node->neighbors_length)];
                    if(neighbor->state == 2){
                        /* notify neighbor's neighbors of unselection */
                        for(int k=0;k<neighbor->neighbors_length;k++){
                            Node* neighborneighbor = neighbor->neighbors[k];

                            int count = 0;
                            for(int l=0;l<neighborneighbor->neighbors_length;l++){
                                Node* neighborneighborneighbor = neighborneighbor->neighbors[l];
                                if(neighborneighborneighbor->state == 2 &&
                                        neighborneighborneighbor->selected_color == neighbor->selected_color){
                                    count++;
                                }
                            }

                            if(count == 1){
                                /* look for selected color in non-available colors */
                                for(int l = neighborneighbor->available_colors_length;
                                        l < neighborneighbor->available_colors_max_length;
                                        l++){
                                    if(neighbor->selected_color ==
                                            neighborneighbor->available_colors[l]){
                                        int_swap(neighborneighbor->available_colors,
                                                 neighborneighbor->available_colors_length++, l);
                                        break;
                                    }
                                }
                            }
                        }
                        neighbor->state = 0;
                        neighbor->selected_color = 0;
                        node_swap(nodes, neighbor->index,
                                  number_of_non_permanents++);
                    }

                }

                if(random(p)){

                    node->state = 1;

                    /* pick a random color */
                    node->selected_color = node->available_colors[
                        randint(0, node->available_colors_length)];
                    
                    /* see if any neighbors have selected it yet */
                    for(int k=0;k<node->signalled_colors_length;k++){
                        if(node->selected_color == node->available_colors[k]){
                            node->state = 0;
                            node->selected_color = 0;
                        }
                    }

                    if(node->state == 1){
                        /* notify neighbors of selection */
                        for(int k=0;k<node->neighbors_length;k++){
                            Node* neighbor = node->neighbors[k];

                            if(neighbor->state == 1 &&
                               neighbor->selected_color == node->selected_color){
                                neighbor->state = 0;
                                continue;
                            }

                            /* look for selected color in
                             * non-signalled available colors */
                            for(int l = neighbor->signalled_colors_length;
                                    l < neighbor->available_colors_length;
                                    l++){
                                if(node->selected_color ==
                                        neighbor->available_colors[l]){
                                    int_swap(neighbor->available_colors,
                                             neighbor->signalled_colors_length++, l);
                                    break;
                                }
                            }
                        }
                    }
                }
            }

            /* reset signals */
            for(int j=0;j<nodes_length;j++){
                nodes[j]->signalled_colors_length = 0;
            }

            /* round 2 */
            for(int j=0;j<number_of_non_permanents;j++){
                Node* node = nodes[j];
                if(node->state == 1){
                    node->state = 2;
                    node_swap(nodes, j, --number_of_non_permanents);
                    for(int k=0;k<node->neighbors_length;k++){
                        Node* neighbor = node->neighbors[k];
                        /* look for selected color in available colors */
                        for(int l=0;l<neighbor->available_colors_length;l++){
                            if(node->selected_color ==
                                    neighbor->available_colors[l]){
                                int_swap(neighbor->available_colors,
                                         --neighbor->available_colors_length, l);
                                break;
                            }
                        }
                    }
                }
            }
        }
        p *= 2;
    }
    return 0;
}


int vc_verify(Node** nodes, int nodes_length,
              int* uncolored, int* same_color_neighbor_pairs){
    *uncolored = 0;
    *same_color_neighbor_pairs = 0;
    for(int i=0;i<nodes_length;i++){
        Node* node = nodes[i];
        if(node->state != 2){
            (*uncolored)++;
        }
        for(int j=0;j<node->neighbors_length;j++){
            Node* neighbor = node->neighbors[j];
            if(node->selected_color == neighbor->selected_color){
                (*same_color_neighbor_pairs)++;
            }
        }
    }
    *same_color_neighbor_pairs /= 2;
    return (*uncolored) + (*same_color_neighbor_pairs);
}
