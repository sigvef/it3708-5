import argparse
import matplotlib.pyplot as plt
import networkx as nx
import sys


def main():

    parser = argparse.ArgumentParser(
        description=
        'Visualizes graphs for use in homework module 5 of it3708. ' +
        'Both the original graph format and the augmented graph format ' +
        'can be visualized. Augmented graphs can be read from stdin by ' +
        'specifying - as the graph path.')
    parser.add_argument('graph_path', metavar='graph_path', type=str,
                        help='the relative path of the graph to visualize')
    parser.add_argument('--spring', action='store_true',
                        help='use springs to layout graph')
    parser.add_argument('--labels', action='store_true',
                        help='show labels on nodes')
    args = parser.parse_args()

    graph = nx.Graph()
    pos = {}
    colors = {}

    if args.graph_path == '-':
        args.graph_path = next(sys.stdin).strip()
        for line in sys.stdin:
            node, color = map(int, line.strip().split(' '))
            if color not in colors:
                colors[color] = []
            colors[color].append(node)

    with open(args.graph_path, 'r') as f:
        number_of_vertices, number_of_edges = map(
            int, next(f).strip().split(' '))
        for _ in range(number_of_vertices):
            i, x, y = next(f).strip().split(' ')
            graph.add_node(int(i))
            pos[int(i)] = map(float, (x, y))
        for i in range(number_of_edges):
            graph.add_edge(*map(int, next(f).strip().split(' ')))

    if args.spring:
        pos = nx.spring_layout(graph)

    fig = plt.figure()
    fig.set_facecolor('white')

    nx.draw_networkx_edges(graph, pos, width=1.0, alpha=0.5)

    nx.draw_networkx_nodes(graph, pos,
                           node_color='black',
                           node_size=500,
                           alpha=0.8)
    color_map = {
        1: 'r',
    }

    for color, nodes in colors.iteritems():
        nx.draw_networkx_nodes(graph, pos,
                               nodelist=nodes,
                               node_color=color_map[color],
                               node_size=500,
                               alpha=0.8)

    if args.labels:
        nx.draw_networkx_labels(graph, pos,
                                font_size=10,
                                font_color=(1, 1, 1, 0.9))

    plt.axis('off')
    plt.show()


if __name__ == '__main__':
    main()
