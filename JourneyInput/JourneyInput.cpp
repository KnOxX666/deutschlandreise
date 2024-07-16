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

bool CheckInput(const std::string& city, const std::vector<std::string>& alreadyEnteredCities, const TopologyData& topologyData)
{
    if (std::find(alreadyEnteredCities.begin(), alreadyEnteredCities.end(), city) != alreadyEnteredCities.end())
    {
        std::cout << "Error: Eingegebene Stadt " << city << " schon eingegeben, bitte eine andere Stadt eingeben!" << std::endl;
        return false;
    }
    if (topologyData.FindNodeData(city) == nullptr)
    {
        std::cout << "Error: Eingegebene Stadt " << city << " unbekannt, bitte eine Stadt eingeben, die im Spiel Deutschlandreise bekannt ist!" << std::endl;
        return false;
    }
    return true;
}

bool IsNumber(const std::string &str) {    
    return !str.empty() && str.find_first_not_of("0123456789") == std::string::npos;
}

DeutschlandreiseInputData JourneyInput::Input (const TopologyData& topologyData) const
{
    DeutschlandreiseInputData inputData;

    std::cout << "Startreisepunkt eingeben: ";
    std::cin >> inputData.originAndDestinationCity;
    if (not CheckInput(inputData.originAndDestinationCity, inputData.transitCities, topologyData))
    {
        exit(1);
    }
    
    std::cout << "Anzahl der Zwischenstopps eingeben: ";
    std::cin >> inputData.numTransitCities;

    for (unsigned int i = 1; i <= inputData.numTransitCities; ++i)
    {
        std::cout << "Bitte " << i << ". Zwischenstopp eingeben: ";
        std::string transitCity;
        std::cin >> transitCity;
        if (CheckInput(transitCity, inputData.transitCities, topologyData))
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