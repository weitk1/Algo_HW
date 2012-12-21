#include <stdlib.h>
#include <stdio.h>

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <set>

#include "Edge.h"
#include "Vertex.h"
using namespace std;

typedef set<int> T_Leaders;

void add_vertex(T_Vertices &vertices, T_Leaders &leaders, int vertex_num)
{
    Vertex &vertex = vertices[vertex_num];
    if (vertex.num == 0) {
        vertex.num = vertex_num;
        vertex.leader_num = vertex.num;
        leaders.insert(vertex_num);
    }
}

int find_leader(const T_Vertices &vertices, const Vertex &vertex)
{
    int vertex_num = vertex.num;
    int leader_num = vertex.leader_num;

    // Leader's leader is itself
    while (vertex_num != leader_num) {
        const Vertex &leader = vertices[leader_num];
        vertex_num = leader.num;
        leader_num = leader.leader_num;
    }

    return vertex_num;
}

int find_max_spacing(const T_Edges &edges, T_Vertices &vertices, T_Leaders &leaders, const int k_clustering)
{
    T_Edges::const_iterator it;
    for (it = edges.begin(); it != edges.end(); ++it) {
        const Vertex &v1 = vertices[it->v1];
        const Vertex &v2 = vertices[it->v2];

        const int v1_leader_num = find_leader(vertices, v1);
        const int v2_leader_num = find_leader(vertices, v2);

        if ((leaders.size() <= k_clustering) &&
            (v1_leader_num != v2_leader_num)) {
            // Vertices in spacing have to be in different cluster
            break;
        }

        if (v1_leader_num == v2_leader_num) {
            // In the same cluster
            continue;
        }

        const Vertex &v1_leader = vertices[v1_leader_num];
        Vertex &v2_leader = vertices[v2_leader_num];

        // v1 becomes the leader of v2
        v2_leader.leader_num = v1_leader.num;

        // Remove v2 from leaders group
        leaders.erase(leaders.find(v2_leader.num));
    }

    return it->length;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage: %s <input_file>", argv[0]);
        exit(EXIT_FAILURE);
    }

    int count, v1, v2, length;
    T_Edges edges;
    T_Vertices vertices;
    T_Leaders leaders;

    string file_name(argv[1]);
    ifstream in_file;
    in_file.open(file_name.c_str(), ifstream::in);
    in_file >> count;
    vertices.resize(count + 1);

    while (!in_file.eof()) {
        in_file >> v1 >> v2 >> length;
        edges.push_back(Edge(v1, v2, length));

        add_vertex(vertices, leaders, v1);
        add_vertex(vertices, leaders, v2);
    }

    sort(edges.begin(), edges.end());

    int k_clustering = 4;
    int max_spacing = find_max_spacing(edges, vertices, leaders, k_clustering);
    printf("Maximum spacing with %d clustering is %d\n", k_clustering, max_spacing);

    exit(EXIT_SUCCESS);
}

