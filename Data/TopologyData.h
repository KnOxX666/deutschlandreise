#pragma once
#include <algorithm>
#include <string>

struct NodeData
{
    std::string cityName;
    size_t id;
    std::string locationInfo;
};

struct EdgeData
{
    const NodeData* origin;
    const NodeData* destination;
    int weight;
    bool isFlight;
};

struct TopologyData
{
    ~TopologyData()
    {
        for (auto& node : nodes) delete node;
        for (auto& edge : edges) delete edge;
    }
    
    const NodeData* FindNodeData(const std::string& idSearchNode) const
    {
        std::vector<NodeData*>::const_iterator it = std::find_if(nodes.begin(), nodes.end(), [=] (const NodeData* nodeData) { return nodeData->cityName == idSearchNode; } );
        if (it == nodes.end()) return nullptr;
        return *it;
    }
    
    std::vector<NodeData*> nodes;
    std::vector<EdgeData*> edges;
};