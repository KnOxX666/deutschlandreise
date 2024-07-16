#include "JourneyCalculator.h"
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include "../Data/DeutschlandreiseData.h"
#include "../Data/TopologyData.h"

JourneyCalculator::JourneyCalculator(const DeutschlandreiseData& _data)
    : data(_data)
    , graph(nullptr)
{
    CreateGraph();
    if (data.IsDetailDebug())
    {
        //Print Graph
        int i = 0;
        for (auto& node : *graph)
        {
            std::cout << data.GetTopologyData().nodes[i]->cityName << "[" << i << "]" << std::endl;
            for (auto& neighbor : node)
            {
                std::cout << "    " << data.GetTopologyData().nodes[neighbor.to]->cityName << std::endl;
            }
            ++i;
        }
    }
}

void JourneyCalculator::CreateGraph()
{
    delete graph;
    graph = new AdjList(data.GetTopologyData().nodes.size());
    for (auto& edge : data.GetTopologyData().edges)
    {
        // add all edges to corresponding origin nodes:
        (*graph)[edge->origin->id].push_back(JourneyCalculator::Edge(edge->destination->id, edge->weight));
        if (not edge->isFlight)
        {
            // the json-data has no returning ways, so create them:
            (*graph)[edge->destination->id].push_back(JourneyCalculator::Edge(edge->origin->id, edge->weight));
        }
    }
}

std::vector<std::string> JourneyCalculator::CreateCompleteRouteCandidate(const std::vector<std::string>& transitCitiesRouteCandidate)
{
    std::vector<std::string> journey;
    journey.push_back(data.GetDeutschlandreiseInputData().originAndDestinationCity);
    for (const auto& city : transitCitiesRouteCandidate) journey.push_back(city);
    journey.push_back(data.GetDeutschlandreiseInputData().originAndDestinationCity);
    return journey;
}

void PrintRoute(const std::vector<std::string>& routeCandidate)
{
    bool isFirst = true;
    for (const auto& city : routeCandidate)
    {
        if (not isFirst) std::cout << " - ";
         std::cout << city;
         isFirst = false;
    }
    std::cout << std::endl;
}

std::vector<std::pair<int,std::vector<int>>> JourneyCalculator::Calculate()
{
    std::vector<std::string> transitCities = data.GetDeutschlandreiseInputData().transitCities;

    std::vector<std::pair<int,std::vector<int>>> bestResults;
    int minDistance = -1;
    do 
    {
        std::vector<std::string> routeCandidate = CreateCompleteRouteCandidate(transitCities);
        if (data.IsDebug())
        {
            std::cout << "    Trying route: ";
            PrintRoute(routeCandidate);
        }
        std::vector<std::pair<int,std::vector<int>>> results;
        for (size_t i = 1; i < routeCandidate.size(); ++i)
        {
            auto result = CalculateShortestRouteUsingDijkstra(data.GetTopologyData().FindNodeData(routeCandidate[i - 1])->id,
                                                              data.GetTopologyData().FindNodeData(routeCandidate[i])->id);
            results.push_back(result);
        }
        int currentDistance = 0;
        for (auto& result : results)
        {
            currentDistance += result.first; 
        }
        if (data.IsDebug()) std::cout << "      -> distance: " << currentDistance;
        if (minDistance == -1 || currentDistance < minDistance)
        {
            minDistance = currentDistance;
            bestResults = results;
            if (data.IsDebug()) std::cout << " *** new optimum! ***";
        } 
        if (data.IsDebug()) std::cout << std::endl;
    } while (std::next_permutation(transitCities.begin(), transitCities.end()));
    
    return bestResults;
}

JourneyCalculator::Node* JourneyCalculator::DetermineMinNodeAndRemove(
    std::vector<JourneyCalculator::Node*>& nodes) const
{
    int minDistance = nodes.front()->distance;
    std::vector<Node*>::iterator bestCandidate = nodes.begin();
    for (std::vector<Node*>::iterator it = nodes.begin(); it != nodes.end(); ++it)
    {
        if (minDistance == -1 || (*it)->distance < minDistance)
        {
            bestCandidate = it;
            minDistance = (*it)->distance;
        }
    }
    Node* minNode = *bestCandidate;
    nodes.erase(bestCandidate);
    return minNode;
}

bool JourneyCalculator::IsContained(const std::vector<Node*>& nodes, int id) const
{
    for (auto node : nodes)
    {
        if (node->id == id) return true;
    }
    return false;
}

std::pair<int,std::vector<int>> JourneyCalculator::CalculateShortestRouteUsingDijkstra(int originId, int destinationId) const
{
    std::vector<Node*> nodes;
    for (auto& node : data.GetTopologyData().nodes)
    {
        nodes.push_back(new Node(node->id));
    }
    
    nodes[originId]->distance = 0; // startpoint's distance always 0.

    std::vector<Node*> toProcess;
    toProcess.push_back(nodes[originId]);
    while (not toProcess.empty())
    {
        Node* minNode = DetermineMinNodeAndRemove(toProcess);
        for (auto& neighbor : (*graph)[minNode->id])
        {
            int weight = neighbor.weight;
            int newDistance = minNode->distance + weight;
            if (nodes[neighbor.to]->distance == -1)
            {
                toProcess.push_back(nodes[neighbor.to]);
                nodes[neighbor.to]->distance = newDistance;
                nodes[neighbor.to]->origin = minNode->id;
            }
            else
            {
                if (   IsContained(toProcess, neighbor.to) 
                    && nodes[neighbor.to]->distance > newDistance)
                {
                    nodes[neighbor.to]->distance = newDistance;
                    nodes[neighbor.to]->origin = minNode->id;
                }
            }
        }
    }
    if (data.IsDetailDebug())
    {
        for (auto& node : nodes)
        {
            std::cout << data.GetTopologyData().nodes[node->id]->cityName << " ["  << node->id  
                << "] dist: " << node->distance << " origin: " 
                << (node->origin == -1 ? "-" : data.GetTopologyData().nodes[node->origin]->cityName) << " [" << node->origin << "]" << std::endl;
        }
    }
    std::pair<int, std::vector<int>> resultDistanceAndShortestRoute;
    resultDistanceAndShortestRoute.first = nodes[destinationId]->distance;

    // create shortest found route from destination node to origin route:

    Node* currentNode = nodes[destinationId];
    while (currentNode->id != originId && currentNode->origin != -1)
    {
        resultDistanceAndShortestRoute.second.push_back(currentNode->id);
        currentNode = nodes[currentNode->origin];
    }
    resultDistanceAndShortestRoute.second.push_back(currentNode->id);
    std::reverse(resultDistanceAndShortestRoute.second.begin(), resultDistanceAndShortestRoute.second.end());

    for (auto node : nodes)
    {
        delete node;
    }
    
    return resultDistanceAndShortestRoute;
}