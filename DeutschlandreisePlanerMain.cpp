#include "JourneyInput/JourneyInput.h"
#include "JourneyCalculator/JourneyCalculator.h"
#include "Data/DeutschlandreiseInputData.h"
#include "Data/DeutschlandreiseData.h"
#include "Data/JSonLoader.h"
#include "Data/TopologyData.h"
#include <iostream>
#include <cstring>

void PrintRoute (
    const std::vector<NodeData*>& nodes, 
    const std::vector<int> route)
{
    bool isFirst = true;
    for (auto& cityId: route)
    {
        if (not isFirst) std::cout << " - ";
        std::cout << nodes[cityId]->cityName << nodes[cityId]->locationInfo;
        isFirst = false;
    }
    std::cout << std::endl;
}

void PrintResults(
    const std::vector<NodeData*>& nodes, 
    const std::vector<std::pair<int,std::vector<int>>>& results)
{
    std::cout << "---====================================================================================================---" << std::endl;
    std::cout << "Optimale Reiseroute: ";
    bool isFirst = true;
    int sumDistance = 0;
    for (auto& result : results)
    {
        if (not isFirst) std::cout << " - ";
        std::cout << nodes[result.second.front()]->cityName << nodes[result.second.front()]->locationInfo;
        isFirst = false;
        sumDistance += result.first;
    }
    std::cout << " - " << nodes[results.back().second.back()]->cityName << nodes[results.back().second.back()]->locationInfo << std::endl;
    std::cout << "Noetige Schritte insgesamt: " << sumDistance / 10 << std::endl;
    std::cout << "----------------------------------------------------------------------------------------------------------" << std::endl;
    std::cout << "Detaillierte Reiseroute:" << std::endl;
    for (auto& result: results)
    {
        std::cout << "    " << nodes[result.second.front()]->cityName << " -> " << nodes[result.second.back()]->cityName 
        << " (Schritte: " << result.first/10 << "):" << std::endl;
        std::cout << "        ";
        PrintRoute(nodes, result.second);
    }
    std::cout << "---====================================================================================================---" << std::endl;
}

int main(int argc, char *argv[])
{
    DeutschlandreiseData data;
    for(size_t i = 0; i < argc; ++i)
    {
        if (std::strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--debug") == 0) data.SetIsDebug(true);
        if (std::strcmp(argv[i], "-dd") == 0 || strcmp(argv[i], "--detailDebug") == 0) data.SetIsDetailDebug(true);
        if (std::strcmp(argv[i], "-t") == 0 || strcmp(argv[i], "--test") == 0) data.SetIsTest(true);
    }
    
    TopologyData* topologyData = JSonLoader().Load();
    data.SetTopologyData(topologyData);

    if (data.IsTest())
    {
        DeutschlandreiseInputData testInputData;
        testInputData.originAndDestinationCity = "Bremen";
        testInputData.transitCities = {"Hamburg", "Dortmund", "Kiel", "Schwerin", "Bielefeld"};
        data.SetDeutschlandreiseInputData(testInputData);
    }
    else
    {
        data.SetDeutschlandreiseInputData(JourneyInput().Input(data.GetTopologyData()));
    }
    
    std::vector<std::pair<int,std::vector<int>>> results = JourneyCalculator(data).Calculate();
    PrintResults(data.GetTopologyData().nodes, results);
    return 0;
}
