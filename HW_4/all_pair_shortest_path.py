#!/usr/bin/env python
import sys
from pprint import pprint

def initialize(edges, source):
    distance = {}

    for vertex in edges:
        distance[vertex] = sys.maxint
    
    distance[source] = 0

    return distance


def relax(u, v, edges, distance):
    if distance[v] > distance[u] + edges[u][v]:
        distance[v] = distance[u] + edges[u][v]

def bellman_ford(edges, source):
    distance = initialize(edges, source)    

    for i in range(len(edges) - 1):
        for u in edges:
            for v in edges[u]:
                relax(u, v, edges, distance)
    
    for u in edges:
        for v in edges[u]:
            assert (distance[v] <= distance[u] + edges[u][v]), "Negative Cycle"

    return distance


if __name__ == '__main__':
    graph_file = sys.argv[1] 

    edges = {}

    with open(graph_file) as in_file:
        num_vertices, num_edges = in_file.readline().split(' ')
        for line in in_file:
            p1, p2, weight = line.split(' ')
            p1 = int(p1)
            p2 = int(p2)
            weight = int(weight)

            # Store edges
            if p1 not in edges:
                edges[p1] = {}
            if p2 not in edges:
                edges[p2] = {}

            edges[p1][p2] = weight

#    pprint(edges)
    distance = bellman_ford(edges, 1)
#    for v in distance:
#        print "Distance from 1 to %d is %d" % (v, distance[v])

