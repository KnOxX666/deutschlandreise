#pragma once
#include <vector>
class TopologyData;

struct Edge
{
    int to;
    int weight;
    Edge(int _to, int _weight) 
        : to(_to)
        , weight(_weight){}
};

typedef std::vector<std::vector<Edge>> AdjList;

class AdjGraph{
public:
    AdjList* CreateGraph(const TopologyData& topologyData) const;
};