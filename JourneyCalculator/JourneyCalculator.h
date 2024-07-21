#pragma once
#include <vector>
#include <string>
#include <map>
#include "AdjGraph.h"

struct DijkstraResult;
class DeutschlandreiseData;

class JourneyCalculator
{
public: 
    explicit JourneyCalculator(const DeutschlandreiseData& _data);
    ~JourneyCalculator();
    std::vector<std::pair<int,std::vector<int>>> Calculate();

private:
    struct Node {
        int id;
        int distance;
        int origin;
        explicit Node(int _id) 
            : id(_id)
            , distance(-1)
            , origin(-1){}         
    };    

    std::vector<std::string> CreateCompleteRouteCandidate(const std::vector<std::string>& transitCitiesRouteCandidate);
    bool IsContained(const std::vector<Node*>& nodes, int id) const;
    Node* DetermineMinNodeAndRemove(std::vector<Node*>& nodes) const;
    std::pair<int,std::vector<int>> CalculateShortestRouteUsingDijkstra(int originId, int destinationId);
    const DeutschlandreiseData& data;
    
    AdjList* graph;

    // origin id is key
    std::map<int, DijkstraResult*> dijstraResults;
};
