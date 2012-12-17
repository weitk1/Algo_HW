#ifndef __ALGO_HW_EDGE_H__
#define __ALGO_HW_EDGE_H__
#include <set>

typedef int Vertex;

struct Edge
{
    Vertex p1;
    Vertex p2;
    int weight;

    Edge()
      : p1(0),
        p2(0),
        weight(0)
    {}

    Edge(Vertex p_1, Vertex p_2, int w)
    {
        p1 = p_1;
        p2 = p_2;
        weight = w;
    }

    Edge(const Edge &e)
      : p1(e.p1),
        p2(e.p2),
        weight(e.weight)
    {}

    Edge& operator=(const Edge &e) {
        p1 = e.p1;
        p2 = e.p2;
        weight = e.weight;
        return *this;
    }

    bool operator<(const Edge &e) const {
        return ((p1 == e.p1 && p2 == e.p2) || (p1 == e.p2 && p2 == e.p1));
    }

    bool operator==(const Edge &e) const {
        return (p1 == e.p1 && p2 == e.p2);
    }
};

#endif // __ALGO_HW_EDGE_H__
