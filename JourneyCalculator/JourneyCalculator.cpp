#include "JourneyCalculator.h"
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include "../Data/DeutschlandreiseData.h"
#include "../Data/TopologyData.h"

JourneyCalculator::JourneyCalculator(const DeutschlandreiseData& _data)
    : data(_data)
{
}

std::vector<std::string> JourneyCalculator::CreateCompleteRouteCandidate(const std::vector<std::string>& transitCitiesRouteCandidate)
{
    std::vector<std::string> journey;
    journey.push_back(data.GetDeutschlandreiseInputData().originAndDestinationCity);
    for (const auto& city : transitCitiesRouteCandidate) journey.push_back(city);
    journey.push_back(data.GetDeutschlandreiseInputData().originAndDestinationCity);
    return journey;
}

void JourneyCalculator::Calculate()
{
    std::vector<std::string> transitCities = data.GetDeutschlandreiseInputData().transitCities;
    
    do 
    {
        std::vector<std::string> routeCandidate = CreateCompleteRouteCandidate(transitCities);
        int length = CalculatePathLength(routeCandidate);
    } while (std::next_permutation(transitCities.begin(), transitCities.end()));
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

struct Node
{
     NodeData* data;
     NodeData* link;
};

void JourneyCalculator::CreateGraph(const std::string& origin, const std::string& destination) const
{
    if (data.IsDebug()) std::cout << "    Creating graph: " << origin << " - " << destination << std::endl;

    const NodeData* nodeData = data.GetTopologyData().FindNodeData(origin);
    
    for (size_t i = 0; i < data.GetTopologyData().edges.size(); ++i)
    {
        if (data.GetTopologyData().edges[i]->origin == nodeData)
        {
            std::cout << " --> " << data.GetTopologyData().edges[i]->destination->id << std::endl;
            
        }
    }
}

int JourneyCalculator::CalculatePathLength(const std::vector<std::string>& routeCandidate) const
{
    if (data.IsDebug())
    {
        std::cout << "Calculating path: ";
        PrintRoute(routeCandidate);
    }
    for (size_t i = 1; i < routeCandidate.size(); ++i)
    {
        CreateGraph(routeCandidate[i - 1], routeCandidate[i]);
        break; // TODO: remove
    }
    return -1;
}