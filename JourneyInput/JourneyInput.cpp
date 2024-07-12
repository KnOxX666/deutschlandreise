#include <iostream>
#include <algorithm>
#include "JourneyInput.h"
#include "../Data/DeutschlandreiseInputData.h"

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

bool CheckInput(const std::string& city, const std::vector<std::string>& alreadyEnteredCities)
{
    if (std::find(alreadyEnteredCities.begin(), alreadyEnteredCities.end(), city) != alreadyEnteredCities.end())
    {
        std::cout << "Error: Eingegebene Stadt " << city << " schon eingegeben, bitte eine andere Stadt eingeben!" << std::endl;
        return false;
    }
    return true;
}

DeutschlandreiseInputData JourneyInput::Input () const
{
    DeutschlandreiseInputData inputData;

    std::cout << "Startreisepunkt eingeben: ";
    std::cin >> inputData.originAndDestinationCity;
    
    for (unsigned int i = 1; i <= 5; ++i)
    {
        std::cout << "Bitte " << i << ". Zwischenstopp eingeben: ";
        std::string transitCity;
        std::cin >> transitCity;
        if (CheckInput(transitCity, inputData.transitCities))
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