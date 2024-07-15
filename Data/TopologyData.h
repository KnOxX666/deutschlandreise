#pragma once
#include <algorithm>

struct NodeData
{
    std::string id;
};

struct EdgeData
{
    const NodeData* origin;
    const NodeData* destination;
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
        std::vector<NodeData*>::const_iterator it = std::find_if(nodes.begin(), nodes.end(), [=] (const NodeData* nodeData) { return nodeData->id == idSearchNode; } );
        if (it == nodes.end()) return nullptr;
        return *it;
    }
    
    std::vector<NodeData*> nodes;
    std::vector<EdgeData*> edges;
};