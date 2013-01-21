#!/usr/bin/env python
import sys
from heapq import heappush, heappop
from pprint import pprint

# Bellman-Ford
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

# Utility function for Johnson's algorithm
def reweight_edges(edges, distance):
    for u in edges.keys():
        for v in edges[u]:
            edges[u][v] = edges[u][v] + distance[u] - distance[v]
    return edges

def restore_edge_weight(positive_edge_weight, u, v, distance):
    orig_edge_weight = positive_edge_weight - distance[u] + distance[v]
    return orig_edge_weight
     

# Dijkstra
def dijkstra(positive_edges, source):
    unvisited_vertices = []
    heap = []
    distance = {} # final distances
    
    for u in positive_edges.keys():
        if u == source:
            distance[source] = 0
            for v in positive_edges[source]:
                heappush(heap, (positive_edges[source][v], u, v))
        else:   
            distance[u] = sys.maxint
            unvisited_vertices.append(u)
            
    
    while (len(unvisited_vertices) > 0):
        try:
            (u_v_len, u, v) = heappop(heap)
        except IndexError:
            # Some vertices are unreachable
            break
        
    return distance
    
if __name__ == '__main__':
    graph_file = sys.argv[1] 

    edges = {}

    with open(graph_file) as in_file:
        num_vertices, num_edges = in_file.readline().split(' ')
        num_vertices = int(num_vertices)
        num_edges = int(num_edges)
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

    try:
        distance = bellman_ford(edges, 1)
    except AssertionError:
        print "Abort because negative-cost cycle exists."

    # Create a special-purpose source vertex s, which has edges of length 0 to every vertex
    edges[0] = {}
    for v in range(1, num_vertices + 1):
        edges[0][v] = 0

    orig_distance = bellman_ford(edges, 0)

    # Re-weight each edge to make all edges positive
    positive_edges = reweight_edges(edges, orig_distance)
    del positive_edges[0]

    print "After reweight"

    # Run Dijkstra for each vertex against new graph and find all pair shortest path
    shortest_path_len = sys.maxint
    shortest_path_u = 0
    shortest_path_v = 0

    total = len(positive_edges.keys())
    count = 1

    for u in positive_edges.keys():
        print "%d/%d" % (count, total)

#        print "Bellman-Ford"
#        distance = bellman_ford(positive_edges, u)

#        print "Dijkstra"
        distance = dijkstra(positive_edges, u)
        
        for v in distance.keys():
            if (u == v):
                continue
            new_shortest_path_len = distance[v] - orig_distance[u] + orig_distance[v]
            if new_shortest_path_len < shortest_path_len:
                shortest_path_len = new_shortest_path_len
                shortest_path_u = u
                shortest_path_v = v
        count += 1
    
    print "u=%d v=%d shortest_path_len=%d" % (shortest_path_u, shortest_path_v, shortest_path_len)

