#include <iostream>
#include <algorithm>
#include "JourneyInput.h"
#include "../Data/DeutschlandreiseInputData.h"
#include "../Data/TopologyData.h"

void AusgabeInput(const DeutschlandreiseInputData& inputData)
{
    std::cout << "Geplante Reise:" << std::endl;
    std::cout << "======================================" << std::endl;
    std::cout << "Start und Zielstadt: " << inputData.originAndDestinationCity << std::endl;
    std::cout << "Zwischenstopps: ";
    bool isFirstCity = true;
    for (auto& city : inputData.transitCities)
    {
        if (not isFirstCity) std::cout << " - ";
        std::cout << city;
        isFirstCity = false;
    }
    std::cout << std::endl;
}

// TODO: Avoid code duplication (also implemented in JSonLoader)
const NodeData* FindNodeData2(const std::vector<NodeData*>& nodes, const std::string& idSearchNode)
{
    std::vector<NodeData*>::const_iterator it = std::find_if(nodes.begin(), nodes.end(), [=] (const NodeData* nodeData) { return nodeData->id == idSearchNode; } );
    if (it == nodes.end()) return nullptr;
    return *it;
}

bool CheckInput(const std::string& city, const std::vector<std::string>& alreadyEnteredCities, const std::vector<NodeData*>& nodeData)
{
    if (std::find(alreadyEnteredCities.begin(), alreadyEnteredCities.end(), city) != alreadyEnteredCities.end())
    {
        std::cout << "Error: Eingegebene Stadt " << city << " schon eingegeben, bitte eine andere Stadt eingeben!" << std::endl;
        return false;
    }
    if (FindNodeData2(nodeData, city) == nullptr)
    {
        std::cout << "Error: Eingegebene Stadt " << city << " unbekannt, bitte eine Stadt eingeben, die im Spiel Deutschlandreise bekannt ist!" << std::endl;
        return false;
    }
    return true;
}

DeutschlandreiseInputData JourneyInput::Input (const std::vector<NodeData*> nodeData) const
{
    DeutschlandreiseInputData inputData;

    std::cout << "Startreisepunkt eingeben: ";
    std::cin >> inputData.originAndDestinationCity;
    if (not CheckInput(inputData.originAndDestinationCity, inputData.transitCities, nodeData))
    {
        exit(1);
    }

    for (unsigned int i = 1; i <= 5; ++i)
    {
        std::cout << "Bitte " << i << ". Zwischenstopp eingeben: ";
        std::string transitCity;
        std::cin >> transitCity;
        if (CheckInput(transitCity, inputData.transitCities, nodeData))
        {
            inputData.transitCities.push_back(transitCity);
        }
        else
        {
            --i;
        }
    }

    AusgabeInput(inputData);
    return inputData;
}