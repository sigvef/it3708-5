#ifndef __VC_H__
#define __VC_H__

#include "graph.h"


int vc(Node** nodes, int nodes_length);
int vc_verify(Node** nodes, int nodes_length,
              int* uncolored, int* same_color_neighbor_pairs);

#endif
