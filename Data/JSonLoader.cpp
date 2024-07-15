#include "JSonLoader.h"
#include <iostream>
#include <fstream>
#include <jsoncpp/json/json.h>
#include <algorithm>
#include "TopologyData.h"

const NodeData* FindNodeData(const std::vector<NodeData*>& nodes, const std::string& idSearchNode)
{
    std::vector<NodeData*>::const_iterator it = std::find_if(nodes.begin(), nodes.end(), [=] (const NodeData* nodeData) { return nodeData->cityName == idSearchNode; } );
    if (it == nodes.end()) abort();
    return *it;
}

TopologyData* JSonLoader::Load()
{
    std::ifstream topology_file("topology.json", std::ifstream::binary);
    Json::Value topology;
    topology_file >> topology;
    
    TopologyData* topologyData = new TopologyData();

    int idCity = 0;
    for (Json::Value::ArrayIndex i = 0; i != topology["nodes"].size(); i++)
    {
        NodeData* node = new NodeData();
        node->cityName = topology["nodes"][i]["id"].asString();
        node->id = idCity;
        topologyData->nodes.push_back(node);
        ++idCity;
    }

    for (Json::Value::ArrayIndex i = 0; i != topology["links"].size(); i++)
    {
        EdgeData* edgeData = new EdgeData();
        edgeData->origin = FindNodeData(topologyData->nodes, topology["links"][i]["source"].asString());
        edgeData->destination = FindNodeData(topologyData->nodes, topology["links"][i]["target"].asString());
        edgeData->weight = topology["links"][i]["weight"].asInt();
        edgeData->isFlight = topology["links"][i]["flight"].asBool();
        topologyData->edges.push_back(edgeData);
        if (edgeData->origin == nullptr || edgeData->destination == nullptr) abort();
    }
    
    return topologyData;
}