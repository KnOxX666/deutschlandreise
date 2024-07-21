#pragma once
#include <vector>
#include "AdjGraph.h"

struct NodeData;

struct DijkstraNodeResult {
    int id;
    int distance;
    int origin;
    explicit DijkstraNodeResult(int _id) 
        : id(_id)
        , distance(-1)
        , origin(-1){}   
};

struct DijkstraResult
{
    DijkstraResult() = default;
    ~DijkstraResult() 
    {
        for (auto result : nodeResults)
        {
            delete result;
        }
    }
    std::vector<DijkstraNodeResult*> nodeResults;
};

class Dijkstra {
public:
    Dijkstra() = default;
    DijkstraResult* Create(const AdjList& graph, const std::vector<NodeData*>& nodes, int originId) const;
private:
    bool IsContained(const std::vector<DijkstraNodeResult*>& nodes, int id) const;
    DijkstraNodeResult* DetermineMinNodeAndRemove(std::vector<DijkstraNodeResult*>& nodes) const;
};