
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
    std::vector<NodeData*> nodes;
    std::vector<EdgeData*> edges;
};