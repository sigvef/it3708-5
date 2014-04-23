import argparse
import matplotlib.pyplot as plt
import networkx as nx
import sys


def main():
    parser = argparse.ArgumentParser(
        description=
        'Visualizes graphs for use in homework module 5 of it3708.')
    parser.add_argument('graph_path', metavar='graph_path', type=str,
                        help='the relative path of the graph file')
    parser.add_argument('color_path', metavar='color_path', nargs='?',
                        type=argparse.FileType('r'), default=sys.stdin,
                        help='the relative path of the coloring file')
    parser.add_argument('--spring', action='store_true',
                        help='use springs to layout graph')
    args = parser.parse_args()

    graph = nx.Graph()
    pos = {}
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
        nx.draw(graph)
    else:
        nx.draw(graph, pos)
    plt.show()


if __name__ == '__main__':
    main()
