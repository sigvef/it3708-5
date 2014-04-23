import argparse
import random
import sys


def main():

    parser = argparse.ArgumentParser(
        description='Generates graphs for use in homework module 5 of it3708.')
    parser.add_argument('number_of_vertices', metavar='NV', type=int,
                        help='the number of vertices in the graph')
    parser.add_argument('number_of_edges', metavar='NE', type=int,
                        help='the number of edges in the graph')

    args = parser.parse_args()

    if args.number_of_vertices < 2:
        print "Error: NV should be at least 2!"
        sys.exit(-1)

    print args.number_of_vertices, args.number_of_edges

    for i in range(args.number_of_vertices):
        print i, random.random() * 256, random.random() * 256

    for i in range(args.number_of_edges):
        vertex_a = random.randint(0, args.number_of_vertices - 1)
        vertex_b = random.randint(0, args.number_of_vertices - 1)
        while vertex_a == vertex_b:
            vertex_b = random.randint(0, args.number_of_vertices - 1)
        print vertex_a, vertex_b

if __name__ == '__main__':
    main()
