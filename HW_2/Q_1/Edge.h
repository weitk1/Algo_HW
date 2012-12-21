#ifndef __ALGO_HW2_EDGE_H__
#define __ALGO_HW2_EDGE_H__

#include <vector>

struct Edge
{
    int v1;
    int v2;
    int length;

    Edge()
      : v1(0),
        v2(0),
        length(0)
    {}

    Edge(int vv1, int vv2, int w)
      : v1(vv1),
        v2(vv2),
        length(w)
    {}

    void operator==(const Edge &e) {
        v1 = e.v1;
        v2 = e.v2;
        length = e.length;
    }

    bool operator<(const Edge &e) const {
        return (length < e.length);
    }
};

typedef std::vector<Edge> T_Edges;

#endif // __ALGO_HW2_EDGE_H__

