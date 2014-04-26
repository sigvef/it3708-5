#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <stdbool.h>


typedef struct Node Node;

struct Node {
    int name;
    double x;
    double y;
    Node** neighbors;
    int neighbors_length;
    int neighbors_max_length;
    int state;
    int selected_color;
    int* available_colors;
    int available_colors_length;
    int available_colors_max_length;
    int signalled_colors_length;
    int index;
};

void read_graph(char* filename, Node*** nodes, int* nodes_length, int n_colors);
void destroy_graph(Node** nodes, int length);
void print_graph(Node** nodes, int length);
void print_node(Node* node);

#endif
