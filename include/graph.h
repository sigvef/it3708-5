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
    bool has_received_signal;
    int state;
};

void read_graph(const char* filename, Node*** nodes, int* nodes_length);
void destroy_graph(Node** nodes, int length);
void print_graph(Node** nodes, int length);
void print_node(Node* node);

#endif
