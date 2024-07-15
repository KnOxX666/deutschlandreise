#pragma once
#include <vector>
#include <string>

class DeutschlandreiseData;

class JourneyCalculator
{
public: 
    explicit JourneyCalculator(const DeutschlandreiseData& _data);
    void Calculate();

private:
    std::vector<std::string> CreateCompleteRouteCandidate(const std::vector<std::string>& transitCitiesRouteCandidate);
    int CalculatePathLength(const std::vector<std::string>& routeCandidate) const;
    void CreateGraph(const std::string& origin, const std::string& destination) const;
    const DeutschlandreiseData& data;
};
