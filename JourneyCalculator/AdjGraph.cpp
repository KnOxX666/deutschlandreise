#include "AdjGraph.h"
#include "../Data/TopologyData.h"

AdjList* AdjGraph::CreateGraph(const TopologyData& topologyData) const
{
    AdjList* graph = new AdjList(topologyData.nodes.size());
    for (auto& edge : topologyData.edges)
    {
        // add all edges to corresponding origin nodes:
        (*graph)[edge->origin->id].push_back(Edge(edge->destination->id, edge->weight));
        if (not edge->isFlight)
        {
            // the json-data has no returning ways, so create them:
            (*graph)[edge->destination->id].push_back(Edge(edge->origin->id, edge->weight));
        }
    }
    return graph;
}