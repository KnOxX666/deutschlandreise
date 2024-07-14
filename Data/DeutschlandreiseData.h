#pragma once
#include <memory>
#include "DeutschlandreiseInputData.h"

class TopologyData;

class DeutschlandreiseData
{
public:
    ~DeutschlandreiseData();
    DeutschlandreiseInputData GetDeutschlandreiseInputData() const;
    void SetDeutschlandreiseInputData(const DeutschlandreiseInputData& deutschlandreiseInputData);
    const TopologyData& GetTopologyData() const;
    void SetTopologyData(TopologyData* topologyData);
    
private:
    DeutschlandreiseInputData deutschlandreiseInputData;
    TopologyData* topologyData;
};