#include "Dijkstra.h"
#include <iostream>
#include "../Data/TopologyData.h"

DijkstraResult* Dijkstra::Create (
    const AdjList& graph, const std::vector<NodeData*>& nodes, int originId) const
{
    DijkstraResult* result = new DijkstraResult();

    for (auto& node : nodes)
    {
        result->nodeResults.push_back(new DijkstraNodeResult(node->id));
    }
    
    result->nodeResults[originId]->distance = 0; // startpoint's distance always 0.

    std::vector<DijkstraNodeResult*> toProcess;
    toProcess.push_back(result->nodeResults[originId]);
    while (not toProcess.empty())
    {
        DijkstraNodeResult* minNode = DetermineMinNodeAndRemove(toProcess);
        for (auto& neighbor : graph[minNode->id])
        {
            int weight = neighbor.weight;
            int newDistance = minNode->distance + weight;
            if (result->nodeResults[neighbor.to]->distance == -1)
            {
                toProcess.push_back(result->nodeResults[neighbor.to]);
                result->nodeResults[neighbor.to]->distance = newDistance;
                result->nodeResults[neighbor.to]->origin = minNode->id;
            }
            else
            {
                if (   IsContained(toProcess, neighbor.to) 
                    && result->nodeResults[neighbor.to]->distance > newDistance)
                {
                    result->nodeResults[neighbor.to]->distance = newDistance;
                    result->nodeResults[neighbor.to]->origin = minNode->id;
                }
            }
        }
    }
    
    return result;
}

bool Dijkstra::IsContained(const std::vector<DijkstraNodeResult*>& nodes, int id) const
{
    for (auto node : nodes)
    {
        if (node->id == id) return true;
    }
    return false;
}

DijkstraNodeResult* Dijkstra::DetermineMinNodeAndRemove(
    std::vector<DijkstraNodeResult*>& nodes) const
{
    int minDistance = nodes.front()->distance;
    std::vector<DijkstraNodeResult*>::iterator bestCandidate = nodes.begin();
    for (std::vector<DijkstraNodeResult*>::iterator it = nodes.begin(); it != nodes.end(); ++it)
    {
        if (minDistance == -1 || (*it)->distance < minDistance)
        {
            bestCandidate = it;
            minDistance = (*it)->distance;
        }
    }
    DijkstraNodeResult* minNode = *bestCandidate;
    nodes.erase(bestCandidate);
    return minNode;
}