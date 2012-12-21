#ifndef __ALGO_HW2_VERTEX_H__
#define __ALGO_HW2_VERTEX_H__

#include <vector>

struct Vertex
{
    int num;
    int leader_num;

    Vertex()
      : num(0),
        leader_num(0)
    {}

    Vertex(int n, int leader_n)
      : num(n),
        leader_num(leader_n)
    {}

    Vertex(const Vertex &v)
      : num(v.num),
        leader_num(v.leader_num)
    {}

    Vertex& operator=(const Vertex &v) {
        num = v.num;
        leader_num = v.leader_num;

        return *this;
    }
};

typedef std::vector<Vertex> T_Vertices;

#endif // __ALGO_HW2_VERTEX_H__

