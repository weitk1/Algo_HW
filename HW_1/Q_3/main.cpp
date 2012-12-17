#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include <set>
#include <map>
#include <algorithm>

#include "edge.h"
using namespace std;

typedef map<Vertex, set<Vertex> > T_Vertices;
typedef map<pair<int, int>, Edge> T_Edges;

void insert_vertice(T_Vertices &vertices, const Vertex &p1, const Vertex &p2)
{
    T_Vertices::iterator it = vertices.find(p1);
    if (it == vertices.end()) {
        set<Vertex> connected_vertices;
        connected_vertices.insert(p2);
        vertices.insert(make_pair(p1, connected_vertices));
    } else {
        it->second.insert(p2); 
    }

    it = vertices.find(p2);
    if (it == vertices.end()) {
        set<Vertex> connected_vertices;
        connected_vertices.insert(p1);
        vertices.insert(make_pair(p2, connected_vertices));
    } else {
        it->second.insert(p1); 
    }
}

int find_MST(T_Vertices &vertices, const T_Edges &edges)
{
    int MST_weight = 0;
    
    set<Vertex> visited_vertices;
    T_Vertices::const_iterator v_it = vertices.begin();
    visited_vertices.insert(v_it->first);
    Edge max_edge(-1, -1, INT_MAX);

    size_t count = 1;
    while (count < vertices.size()) {
        Edge least_cost_edge = max_edge;
        for (set<Vertex>::const_iterator vv_it = visited_vertices.begin(); vv_it != visited_vertices.end(); ++vv_it) {
            printf("%d =>", *vv_it);
            
            v_it = vertices.find(*vv_it);
    
            for (set<Vertex>::const_iterator cv_it = v_it->second.begin(); cv_it != v_it->second.end(); ++cv_it) {
                printf(" %d", *cv_it);

                if (visited_vertices.find(*cv_it) != visited_vertices.end()) {
                    continue;
                }
                
                pair<int, int> candidate_edge = make_pair(v_it->first, *cv_it);
                T_Edges::const_iterator edge_it = edges.find(candidate_edge);
                if (edge_it == edges.end()) {
                    fprintf(stderr, "No such edge: (%d %d)\n", candidate_edge.first, candidate_edge.second);
                }

                if (edge_it->second.weight < least_cost_edge.weight) {
                    least_cost_edge = edge_it->second;
                }
            }
            printf("\n");
        }
        if (visited_vertices.find(least_cost_edge.p1) == visited_vertices.end()) {
            visited_vertices.insert(least_cost_edge.p1);
        } else {
            visited_vertices.insert(least_cost_edge.p2);
        }

        printf("%d %d %d\n", least_cost_edge.p1, least_cost_edge.p2, least_cost_edge.weight);
        MST_weight += least_cost_edge.weight;
        ++count;
        least_cost_edge = max_edge;
    }

    return MST_weight;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: \n");
        exit(EXIT_FAILURE);
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        fprintf(stderr, "Error opening file %s: %s\n", argv[1], strerror(errno));
        exit(EXIT_FAILURE);
    }

    char line[128];
    if (NULL == fgets(line, sizeof(line), fp)) {
        fprintf(stderr, "Error reading file %s: %s\n", argv[1], strerror(errno));
        exit(EXIT_FAILURE);
    }

    int num_vertices = 0, num_edges = 0;
    int parse_ret = sscanf(line, "%d %d", &num_vertices, &num_edges);
    if (parse_ret != 2) {
        fprintf(stderr, "Error parsing line '%s'\n", line);
        exit(EXIT_FAILURE);
    }
    printf("Num of vertices: %d, Num of edges: %d\n", num_vertices, num_edges);
    T_Vertices vertices;
    T_Edges edges;

    int p1, p2, weight;
    for (int i = 0; i < num_edges; ++i) {
        fgets(line, sizeof(line), fp);
        int parse_ret = sscanf(line, "%d %d %d", &p1, &p2, &weight);
        if (parse_ret != 3) {
            fprintf(stderr, "Error parsing line '%s'\n", line);
            exit(EXIT_FAILURE);
        }
        printf("Read %d, %d, %d\n", p1, p2, weight);
        edges.insert(make_pair(make_pair(p1, p2), Edge(p1, p2, weight)));
        edges.insert(make_pair(make_pair(p2, p1), Edge(p2, p1, weight)));
        insert_vertice(vertices, p1, p2);
    }

    fclose(fp);

    printf("MST weight: %d\n", find_MST(vertices, edges));

    exit(EXIT_SUCCESS);
}
