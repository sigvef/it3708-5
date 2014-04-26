#ifndef __MIS_H__
#define __MIS_H__

#include "graph.h"


int mis(Node** nodes, int nodes_length, int* active_nodes);
int mis_verify(Node** nodes, int nodes_length, int* adjacent_leader_pairs,
               int* leaderless_nodes);

#endif
