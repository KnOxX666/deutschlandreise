#pragma once
#include <vector>
#include <string>

class DeutschlandreiseData;

class JourneyCalculator
{
public: 
    explicit JourneyCalculator(const DeutschlandreiseData& _data);
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
    
    struct Edge
    {
        int to;
        int weight;
        Edge(int _to, int _weight) 
            : to(_to)
            , weight(_weight){}
    };

    std::vector<std::string> CreateCompleteRouteCandidate(const std::vector<std::string>& transitCitiesRouteCandidate);
    int CalculatePathLength(const std::vector<std::string>& routeCandidate) const;
    void CreateGraph();
    bool IsContained(const std::vector<Node*>& nodes, int id) const;
    Node* DetermineMinNodeAndRemove(std::vector<Node*>& nodes) const;
    std::pair<int,std::vector<int>> CalculateShortestRouteUsingDijkstra(int originId, int destinationId) const;
    const DeutschlandreiseData& data;
    
    
    typedef std::vector<std::vector<Edge>> AdjList;
    AdjList* graph;
};
