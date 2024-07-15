#pragma once
#include <vector>
class DeutschlandreiseInputData;
class TopologyData;

class JourneyInput
{
public:
    DeutschlandreiseInputData Input (const TopologyData& topologyData) const;
};