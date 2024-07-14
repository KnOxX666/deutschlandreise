#pragma once
#include <memory>
#include "DeutschlandreiseInputData.h"

class TopologyData;

class DeutschlandreiseData
{
public:
    DeutschlandreiseData();
    ~DeutschlandreiseData();
    DeutschlandreiseInputData GetDeutschlandreiseInputData() const;
    void SetDeutschlandreiseInputData(const DeutschlandreiseInputData& deutschlandreiseInputData);
    const TopologyData& GetTopologyData() const;
    void SetTopologyData(TopologyData* topologyData);
    void SetIsDebug(bool isDebug);
    bool IsDebug() const;
    
private:
    DeutschlandreiseInputData deutschlandreiseInputData;
    TopologyData* topologyData;
    bool isDebug;
};