#include "JourneyCalculator.h"
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include "Dijkstra.h"
#include "../Data/DeutschlandreiseData.h"
#include "../Data/TopologyData.h"

JourneyCalculator::JourneyCalculator(const DeutschlandreiseData& _data)
    : data(_data)
    , graph(AdjGraph().CreateGraph(data.GetTopologyData()))
{
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

JourneyCalculator::~JourneyCalculator()
{
    delete graph;
    for (auto result : dijstraResults)
    {
        delete result.second;
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

std::pair<int,std::vector<int>> JourneyCalculator::CalculateShortestRouteUsingDijkstra(int originId, int destinationId)
{
    DijkstraResult* dijstraResult = nullptr;
    std::map<int, DijkstraResult*>::const_iterator it = dijstraResults.find(originId);
    if (it == dijstraResults.end())
    {
        dijstraResult = Dijkstra().Create(*graph,data.GetTopologyData().nodes, originId);
        dijstraResults[originId] = dijstraResult;
    }
    else
    {
        dijstraResult = it->second;
    }
    
    if (data.IsDetailDebug())
    {
        for (auto& node : dijstraResult->nodeResults)
        {
            std::cout << data.GetTopologyData().nodes[node->id]->cityName << " ["  << node->id  
                << "] dist: " << node->distance << " origin: " 
                << (node->origin == -1 ? "-" : data.GetTopologyData().nodes[node->origin]->cityName) << " [" << node->origin << "]" << std::endl;
        }
    }

    std::pair<int, std::vector<int>> resultDistanceAndShortestRoute;
    resultDistanceAndShortestRoute.first = dijstraResult->nodeResults[destinationId]->distance;

    // create shortest found route from destination node to origin route:

    DijkstraNodeResult* currentNode = dijstraResult->nodeResults[destinationId];
    while (currentNode->id != originId && currentNode->origin != -1)
    {
        resultDistanceAndShortestRoute.second.push_back(currentNode->id);
        currentNode = dijstraResult->nodeResults[currentNode->origin];
    }
    resultDistanceAndShortestRoute.second.push_back(currentNode->id);
    std::reverse(resultDistanceAndShortestRoute.second.begin(), resultDistanceAndShortestRoute.second.end());
    
    return resultDistanceAndShortestRoute;
}